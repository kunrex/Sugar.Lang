#include "cil_transpiler.h"

#include <format>
#include <fstream>
#include <filesystem>

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/transpile_file_exception.h"
#include "../../Structure/Context/Control/return.h"
#include "../../Structure/Context/Entities/this_context.h"
#include "../../Structure/Context/Entities/Functions/copy_context.h"
#include "../../Structure/Context/Entities/Functions/creation_context.h"
#include "../../Structure/Context/Entities/Functions/format_context.h"
#include "../../Structure/Context/Entities/Functions/funcref_context.h"
#include "../../Structure/Context/Entities/Functions/function_call_context.h"
#include "../../Structure/Context/Entities/Functions/invoke_context.h"
#include "../../Structure/Context/Entities/Functions/ref_context.h"
#include "../../Structure/Context/Entities/References/field_context.h"
#include "../../Structure/Context/Entities/References/local_variable_context.h"
#include "../../Structure/Context/Entities/References/parameter_context.h"
#include "../../Structure/Context/Entities/References/property_context.h"
#include "../../Structure/Context/Expressions/assignment_expression.h"
#include "../../Structure/Context/Expressions/dot_expression.h"
#include "../../Structure/Context/Expressions/indexer_expression.h"
#include "../../Structure/Core/DataTypes/data_type.h"

#include "../../Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"
#include "../../Structure/Global/Functions/function_extensions.h"

#include "../../Structure/Local/Scopes/scope.h"
#include "../../Structure/Wrappers/Generic/array.h"
#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Reference/void.h"
#include "../../Structure/Wrappers/Value/integer.h"

using namespace std;
namespace fs = filesystem;

using namespace Services;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

const string open_flower = "\n{\n";
const string close_flower = "\n}\n";

const string prefix_auto = "auto";
const string prefix_ansi = "ansi";
const string prefix_sealed = "sealed";
const string prefix_extends = "extends";
const string prefix_sequential = "sequential";
const string prefix_before = "beforefieldinit";

const string ms_core_enum = "[System.Runtime]System.Enum";
const string ms_core_class = "[System.Runtime]System.Object";
const string ms_core_struct = "[System.Runtime]System.TypeValue";

const string pop = "pop";
const string dup = "dup";
const string load_this = "ldarg.0";

namespace Analysis::Creation
{
    std::optional<string> CreateOutputFile(const string& outputDirectory, const string& fileName)
    {
        const auto outputFile = outputDirectory / fs::path(fileName);

        if (std::ofstream file(outputFile); file.is_open())
        {
            file.close();
            return string(outputFile);
        }

        ExceptionManager::Instance().AddChild(new TranspileFileException(outputFile));
        return std::nullopt;
    }

    string AccessModifierString(const IDescribable* const describer) { return describer->CheckDescriber(Describer::Public) ? "public" : "private"; }

    string DataTypeStaticString(const IDescribable* const describer) { return describer->CheckDescriber(Describer::Static) ? "sealed abstract" : "sealed"; }

    string FieldDescriberString(const IDescribable* const describer)
    {
        std::vector<string> describers;

        describers.emplace_back(AccessModifierString(describer));

        if (describer->CheckDescriber(Describer::Const))
            describers.emplace_back("literal");
        else if (describer->CheckDescriber(Describer::Static))
            describers.emplace_back("static");

        if (describer->CheckDescriber(Describer::Constexpr))
            describers.emplace_back("initonly");

        if (!describers.empty())
        {
            string result;
            for (const auto& value: describers)
                result += value;

            return result;
        }

        return "";
    }

    string FunctionStaticString(const IDescribable* const describer) { return describer->CheckDescriber(Describer::Static) ? "static" : "instance"; }

    string FunctionParametersString(const IScoped* const function)
    {
        string parameters;
        const auto parameterCount = function->ParameterCount();

        for (auto i = 0; i < parameterCount; i++)
        {
            const auto parameter = *function->VariableAt(i);
            parameters += std::format("{} {}{}", parameter.CreationType()->FullName(), parameter.Name(), i < parameterCount - 1 ? "," : "");
        }

        return parameters;
    }

    string FunctionVariablesString(const IScoped* const function)
    {
        string variables;
        const auto variableCount = function->VariableCount() + function->ParameterCount();

        for (auto i = 0; i < variableCount; i++)
        {
            const auto variable = *function->VariableAt(i);
            variables += std::format("{} {}{}", variable.CreationType()->FullName(), variable.Name(), i < variableCount- 1 ? "," : "");
        }

        return variables;
    }

    string TranspileConstantString(const ICharacteristic* const characteristic)
    {
        switch (characteristic->CreationType()->Type())
        {
            case TypeKind::Short:
                return std::format("int16({})", *reinterpret_cast<const short*>(characteristic->Context()->Metadata()));
            case TypeKind::Int:
                return std::format("int32({})", *reinterpret_cast<const int*>(characteristic->Context()->Metadata()));
            case TypeKind::Long:
                return std::format("int64({})", *reinterpret_cast<const long*>(characteristic->Context()->Metadata()));
            case TypeKind::Float:
                return std::format("float32({})", *reinterpret_cast<const float*>(characteristic->Context()->Metadata()));
            case TypeKind::Double:
                return std::format("float64({})", *reinterpret_cast<const double*>(characteristic->Context()->Metadata()));
            case TypeKind::Boolean:
                return std::format("bool({})", *reinterpret_cast<const bool*>(characteristic->Context()->Metadata()));
            case TypeKind::Character:
                return std::format("char()", static_cast<int>(*reinterpret_cast<const char*>(characteristic->Context()->Metadata())));
            case TypeKind::String:
                return "" + *reinterpret_cast<const string*>(characteristic->Context()->Metadata()) + "";
            default:
                return "";
        }
    }

    void TranspileLoad(const IContextNode* context, StringBuilder& stringBuilder);
    void TranspileLoad(const IContextNode* current, const IContextNode* context, StringBuilder& stringBuilder);

    void TranspileExpression(const IContextNode* context, StringBuilder& stringBuilder);

    void TranspileLoadField(const IContextNode* const fieldContext, StringBuilder& stringBuilder, const bool loadAddress)
    {
        const auto field = reinterpret_cast<const ICharacteristic*>(fieldContext->Metadata());
        const auto instruction = loadAddress && field->CreationType()->MemberType() != MemberType::Class ? "flda" : "fld";

        if (field->CheckDescriber(Describer::Constexpr))
            stringBuilder.PushLine(field->Context()->CILData());
        else if (field->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(std::format("lds{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
        else
        {
            stringBuilder.PushLine(load_this);
            stringBuilder.PushLine(std::format("ld{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
        }
    }

    void TranspileLoadField(const IContextNode* const fieldContext, const IContextNode* const context, StringBuilder& stringBuilder, const bool loadAddress)
    {
        const auto field = reinterpret_cast<const ICharacteristic*>(fieldContext->Metadata());
        const auto instruction = loadAddress && field->CreationType()->MemberType() != MemberType::Class ? "flda" : "fld";

        if (field->CheckDescriber(Describer::Constexpr))
        {
            if (context->MemberType() != MemberType::StaticReferenceContext)
                stringBuilder.PushLine(pop);

            stringBuilder.PushLine(field->Context()->CILData());
        }
        else if (field->CheckDescriber(Describer::Static))
        {
            if (context->MemberType() != MemberType::StaticReferenceContext)
                stringBuilder.PushLine(pop);

            stringBuilder.PushLine(std::format("lds{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
        }
        else
            stringBuilder.PushLine(std::format("ld{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
    }

    void TranspileLoadProperty(const IContextNode* const propertyContext, StringBuilder& stringBuilder)
    {
        const auto property = reinterpret_cast<const PropertyDefinition*>(propertyContext->Metadata());
        if (!property->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(load_this);

        stringBuilder.PushLine(property->SignatureGetString());
    }

    void TranspileLoadProperty(const IContextNode* const propertyContext, const IContextNode* const context, StringBuilder& stringBuilder)
    {
        const auto property = reinterpret_cast<const PropertyDefinition*>(propertyContext->Metadata());
        if (property->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
            stringBuilder.PushLine(pop);

        stringBuilder.PushLine(property->SignatureGetString());
    }

    void TranspileLoadArguments(const IContextNode* const arguments, const int offset, StringBuilder& stringBuilder)
    {
        const auto childCount = arguments->ChildCount();

        for (auto i = offset; i < childCount; i++)
            TranspileExpression(arguments->GetChild(i), stringBuilder);
    }

    void TranspileFunctionCall(const IContextNode* const functionCallContext, StringBuilder& stringBuilder)
    {
        TranspileLoadArguments(functionCallContext, 1, stringBuilder);
        if (const auto function = reinterpret_cast<const IFunctionDefinition*>(functionCallContext->Metadata()); !function->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(load_this);

        stringBuilder.PushLine(functionCallContext->CILData());
    }

    void TranspileFunctionCall(const IContextNode* const functionCallContext, const IContextNode* const context, StringBuilder& stringBuilder)
    {
        if (const auto function = reinterpret_cast<const IFunctionDefinition*>(functionCallContext->Metadata()); function->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
            stringBuilder.PushLine(pop);

        stringBuilder.PushLine(functionCallContext->CILData());
    }

    void TranspileIndexerExpression(const IContextNode* const indexerExpression, StringBuilder& stringBuilder)
    {
        TranspileLoad(indexerExpression->GetChild(0), stringBuilder);
        TranspileLoadArguments(indexerExpression, 1, stringBuilder);

        stringBuilder.PushLine(reinterpret_cast<const IIndexerDefinition*>(indexerExpression->Metadata())->SignatureGetString());
    }

    void TranspileIndexerExpression(const IContextNode* const indexerExpression, const IContextNode* const context, StringBuilder& stringBuilder)
    {
        TranspileLoad(indexerExpression->GetChild(0), context, stringBuilder);
        TranspileLoadArguments(indexerExpression, 1, stringBuilder);

        stringBuilder.PushLine(reinterpret_cast<const IIndexerDefinition*>(indexerExpression->Metadata())->SignatureGetString());
    }

    void TranspileLoadDotLHS(const IContextNode* const lhs, const IContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (lhs->MemberType())
        {
            case MemberType::FieldContext:
                TranspileLoadField(lhs, context, stringBuilder, true);
                break;
            case MemberType::PropertyContext:
                TranspileLoadProperty(lhs, context, stringBuilder);
                break;
            case MemberType::FunctionCallContext:
                TranspileFunctionCall(lhs, context, stringBuilder);
                break;
            case MemberType::IndexerExpression:
                TranspileIndexerExpression(lhs, context, stringBuilder);
                break;
            default:
                break;
        }
    }

    void TranspileLoadDotLHS(const IContextNode* const lhs, StringBuilder& stringBuilder)
    {
        switch (lhs->MemberType())
        {
            case MemberType::FieldContext:
                TranspileLoadField(lhs, stringBuilder, true);
                break;
            case MemberType::PropertyContext:
                TranspileLoadProperty(lhs, stringBuilder);
                break;
            case MemberType::LocalVariableContext:
                {
                    const auto variable = reinterpret_cast<const IVariable*>(lhs->Metadata());
                    stringBuilder.Push(std::format("ldloc{}.{}", variable->CreationType()->MemberType() == MemberType::Class ? "" : "a", lhs->CILData()));
                }
                break;
            case MemberType::FunctionParameterContext:
                {
                    const auto variable = reinterpret_cast<const IVariable*>(lhs->Metadata());
                    stringBuilder.Push(std::format("ldarg{}.{}", variable->CreationType()->MemberType() == MemberType::Class ? "" : "a", lhs->CILData()));
                }
                break;
            case MemberType::FunctionCallContext:
                TranspileFunctionCall(lhs, stringBuilder);
                break;
            case MemberType::IndexerExpression:
                TranspileIndexerExpression(lhs, stringBuilder);
                break;
            default:
                TranspileLoad(lhs, stringBuilder);
        }
    }

    void TranspileLoad(const IContextNode* const current, const IContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (current->MemberType())
        {
            case MemberType::DotExpression:
                {
                    TranspileLoadDotLHS(current->GetChild(static_cast<int>(ChildCode::LHS)), context, stringBuilder);
                    TranspileLoad(current->GetChild(static_cast<int>(ChildCode::RHS)), current->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                }
            case MemberType::FieldContext:
                TranspileLoadField(current, context, stringBuilder, false);
                break;
            case MemberType::PropertyContext:
            case MemberType::IndexerExpression:
            case MemberType::FunctionCallContext:
                TranspileLoadDotLHS(current, context, stringBuilder);
                break;
            default:
                break;
        }
    }

    void TranspileListCollection(const IDataType* const listType, const IContextNode* const arguments, StringBuilder& stringBuilder)
    {
        stringBuilder.PushLine(listType->FindConstructor({ })->FullName());
        if (arguments->ChildCount() == 0)
            return;

        const auto addString = listType->FindFunction("Add", { arguments->GetChild(0)->CreationType() })->FullName();

        for (auto i = 0; i < arguments->ChildCount(); i++)
        {
            if (i++ < arguments->ChildCount() - 1)
                stringBuilder.PushLine(dup);

            TranspileExpression(arguments->GetChild(i), stringBuilder);
            stringBuilder.PushLine(addString);
        }
    }

    void TranspileArrayCollection(const IDataType* const arrayType, const IContextNode* const arguments, StringBuilder& stringBuilder)
    {
        stringBuilder.PushLine("ldc.i4 " + std::to_string(arguments->ChildCount()));
        stringBuilder.PushLine(arrayType->FindConstructor({ &Integer::Instance() })->FullName());

        const auto indexerString = arrayType->FindIndexer({ &Integer::Instance() })->SignatureSetString();

        for (auto i = 0; i < arguments->ChildCount(); i++)
        {
            if (i++ < arguments->ChildCount() - 1)
                stringBuilder.PushLine(dup);

            stringBuilder.PushLine("ldc.i4 " + std::to_string(i++));
            TranspileExpression(arguments->GetChild(i), stringBuilder);
            stringBuilder.PushLine(indexerString);
        }
    }

    const IContextNode* TranspileReturnLoad(const IContextNode* const initialContext, StringBuilder& stringBuilder)
    {
        if (initialContext->MemberType() == MemberType::DotExpression)
        {
            auto context = initialContext->GetChild(static_cast<int>(ChildCode::LHS));
            auto current = initialContext->GetChild(static_cast<int>(ChildCode::RHS));

            TranspileLoad(initialContext->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);

            while (true)
            {
                switch (current->MemberType())
                {
                    case MemberType::DotExpression:
                        {
                            TranspileLoad(current->GetChild(static_cast<int>(ChildCode::LHS)), context, stringBuilder);

                            context = current->GetChild(static_cast<int>(ChildCode::LHS));
                            current = current->GetChild(static_cast<int>(ChildCode::RHS));
                        }
                        continue;
                    case MemberType::IndexerExpression:
                        TranspileLoad(current->GetChild(0), context, stringBuilder);
                        break;
                    case MemberType::FieldContext:
                        {
                            if (const auto field = reinterpret_cast<const ICharacteristic*>(current->Metadata()); field->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
                                stringBuilder.PushLine(pop);
                        }
                        break;
                    case MemberType::PropertyContext:
                        {
                            if (const auto property = reinterpret_cast<const PropertyDefinition*>(current->Metadata()); property->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
                                stringBuilder.PushLine(pop);
                        }
                        break;
                    case MemberType::FunctionCallContext:
                        {
                            if (const auto function = reinterpret_cast<const IFunctionDefinition*>(current->Metadata()); function->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
                                stringBuilder.PushLine(pop);
                        }
                    default:
                        break;
                }

                return current;
            }
        }

        return initialContext;
    }

    void TranspileLoad(const IContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case MemberType::DotExpression:
                {
                    TranspileLoadDotLHS(context->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                    TranspileLoad(context->GetChild(static_cast<int>(ChildCode::RHS)), context->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                }
                break;
            case MemberType::FieldContext:
                TranspileLoadField(context, stringBuilder, false);
                break;
            case MemberType::PropertyContext:
                TranspileLoadProperty(context, stringBuilder);
                break;
            case MemberType::LocalVariableContext:
                stringBuilder.PushLine("ldloc." + context->CILData());
                break;
            case MemberType::FunctionParameterContext:
                stringBuilder.PushLine("ldarg." + context->CILData());
                break;
            case MemberType::FunctionCallContext:
                TranspileFunctionCall(context, stringBuilder);
                break;
            case MemberType::IndexerExpression:
                TranspileIndexerExpression(context, stringBuilder);
                break;
            case MemberType::PrintContext:
            case MemberType::InputContext:
            case MemberType::ConstantContext:
                stringBuilder.PushLine(context->CILData());
            case MemberType::FormatContext:
                {
                    for (auto i = 0; i < context->ChildCount(); i++)
                    {
                        const auto child = context->GetChild(i);
                        TranspileExpression(child, stringBuilder);

                        if (child->MemberType() != MemberType::Class)
                            stringBuilder.PushLine(std::format("box {}", child->CreationType()->FullName()));
                    }

                    stringBuilder.Push(context->CILData());
                }
                break;
            case MemberType::FormatSingleContext:
                {
                    const auto operand = context->GetChild(static_cast<int>(ChildCode::Expression));

                    TranspileExpression(operand, stringBuilder);
                    if (operand->CreationType()->MemberType() != MemberType::Class)
                        stringBuilder.PushLine(std::format("box {}", operand->CreationType()->FullName()));

                    stringBuilder.Push(context->CILData());
                }
                break;
            case MemberType::FormatDoubleContext:
                {
                    const auto lhs = context->GetChild(static_cast<int>(ChildCode::LHS)), rhs = context->GetChild(static_cast<int>(ChildCode::RHS));

                    TranspileExpression(lhs, stringBuilder);
                    if (lhs->CreationType()->MemberType() != MemberType::Class)
                        stringBuilder.PushLine(std::format("box {}", lhs->CreationType()->FullName()));

                    TranspileExpression(rhs, stringBuilder);
                    if (rhs->CreationType()->MemberType() != MemberType::Class)
                        stringBuilder.PushLine(std::format("box {}", rhs->CreationType()->FullName()));

                    stringBuilder.Push(context->CILData());
                }
                break;
            case MemberType::InvokeContext:
                {
                    TranspileLoadArguments(context, 0, stringBuilder);
                    stringBuilder.PushLine(context->CILData());
                }
                break;
            case MemberType::FuncRefContext:
                {
                    if (const auto operand = context->GetChild(static_cast<int>(ChildCode::Expression)); operand->MemberType() != MemberType::StaticReferenceContext)
                        TranspileLoad(operand, stringBuilder);

                    stringBuilder.Push(context->CILData());
                }
                break;
            case MemberType::CollectorConstructorCallContext:
                {
                    if (context->CreationType()->Type() == TypeKind::List)
                        return TranspileListCollection(context->CreationType(), context, stringBuilder);

                    return TranspileArrayCollection(context->CreationType(), context, stringBuilder);
                }
                break;
            case MemberType::RefContext:
                {
                    switch (const auto finalContext = TranspileReturnLoad(context->GetChild(static_cast<int>(ChildCode::Expression)), stringBuilder); finalContext->MemberType())
                    {
                        case MemberType::FieldContext:
                            {
                                const auto field = reinterpret_cast<const ICharacteristic*>(finalContext->Metadata());
                                stringBuilder.PushLine(std::format("ld{}flda {} {}", field->CheckDescriber(Describer::Static) ? "s" : "", field->CreationType()->FullName(), field->FullName()));
                            }
                            break;
                        case MemberType::LocalVariableContext:
                            stringBuilder.PushLine("ldloca." + finalContext->CILData());
                            break;
                        case MemberType::FunctionParameterContext:
                            stringBuilder.PushLine("ldlarga." + finalContext->CILData());
                            break;
                        default:
                            break;
                    }
                }
                break;
            case MemberType::CopyContext:
                {
                    const auto operand = context->GetChild(static_cast<int>(ChildCode::Expression));

                    TranspileExpression(operand, stringBuilder);
                    switch (const auto creationType = operand->CreationType(); creationType->Type())
                    {
                        case TypeKind::Short:
                            stringBuilder.Push("ldind.i2");
                            break;
                        case TypeKind::Int:
                            stringBuilder.Push("ldind.i4");
                            break;
                        case TypeKind::Long:
                            stringBuilder.Push("ldind.i8");
                            break;
                        case TypeKind::Float:
                            stringBuilder.Push("ldind.r4");
                            break;
                        case TypeKind::Double:
                            stringBuilder.Push("ldind.r8");
                            break;
                        case TypeKind::Boolean:
                            stringBuilder.Push("ldind.i1 conv.i4");
                            break;
                        case TypeKind::Character:
                            stringBuilder.Push("ldind.u2 conv.i4");
                            break;
                        default:
                            stringBuilder.Push("ldobj " + creationType->FullName());
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }

    void TranspileExpression(const IContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case MemberType::CastExpression:
            case MemberType::UnaryExpression:
                {
                    const auto unaryExpression = dynamic_cast<const UnaryContextNode*>(context);
                    TranspileExpression(unaryExpression->GetChild(static_cast<int>(ChildCode::Expression)), stringBuilder);
                    stringBuilder.PushLine(unaryExpression->CILData());
                }
                break;
            case MemberType::BinaryExpression:
                {
                    const auto binaryExpression = dynamic_cast<const BinaryContextNode*>(context);
                    TranspileExpression(binaryExpression->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                    TranspileExpression(binaryExpression->GetChild(static_cast<int>(ChildCode::RHS)), stringBuilder);
                    stringBuilder.PushLine(binaryExpression->CILData());
                }
                break;
            case MemberType::AssignmentExpression:
                {
                    const auto finalContext = TranspileReturnLoad(context->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                    const auto rhs = context->GetChild(static_cast<int>(ChildCode::RHS));

                    if (finalContext->MemberType() == MemberType::IndexerExpression)
                    {
                        TranspileLoadArguments(finalContext, 1, stringBuilder);

                        TranspileExpression(rhs, stringBuilder);
                        stringBuilder.PushLine(reinterpret_cast<const IIndexerDefinition*>(finalContext->Metadata())->SignatureSetString());
                        break;
                    }

                    TranspileExpression(rhs, stringBuilder);
                    stringBuilder.PushLine(dup);

                    switch (finalContext->MemberType())
                    {
                        case MemberType::FieldContext:
                            {
                                const auto field = reinterpret_cast<const ICharacteristic*>(finalContext->Metadata());
                                stringBuilder.PushLine(std::format("st{}fld {} {}", field->CheckDescriber(Describer::Static) ? "s" : "", field->CreationType()->FullName(), field->FullName()));
                            }
                            break;
                        case MemberType::PropertyContext:
                            stringBuilder.PushLine(reinterpret_cast<const PropertyDefinition*>(finalContext->Metadata())->SignatureSetString());
                            break;
                        case MemberType::LocalVariableContext:
                            stringBuilder.PushLine("stloc." + finalContext->CILData());
                            break;
                        case MemberType::FunctionParameterContext:
                            stringBuilder.PushLine("starg." + finalContext->CILData());
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                TranspileLoad(context, stringBuilder);
                break;
        }
    }

    void TranspileContext(const IContextNode* context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case MemberType::Throw:
            case MemberType::Return:
            case MemberType::BranchJump:
                stringBuilder.PushLine(context->CILData());
                break;
            default:
                {
                    TranspileExpression(context, stringBuilder);
                    if (context->Readable())
                        stringBuilder.PushLine(pop);
                }
                break;
        }
    }

    CILTranspiler::CILTranspiler(string name, string directory, const SourceDirectory* const source) : projectName(std::move(name)), projectDirectory(std::move(directory)), projectLocation(), source(source), stringBuilder()
    {
        const auto outputDirectory = fs::path(std::format("{}/{}/bin", projectDirectory, projectName));
        if (!exists(outputDirectory))
        {
            if (create_directories(outputDirectory))
                std::cout << "Output directory created: " << outputDirectory << std::endl;
            else
            {
                ExceptionManager::Instance().AddChild(new TranspileFileException(outputDirectory));
                return;
            }
        }

        const auto programSource = source->GetChild("program");
        if (programSource == nullptr || programSource->SourceType() != SourceType::File)
        {
            //exception
            return;
        }

        const auto sourceFile = dynamic_cast<const SourceFile*>(programSource);
        const auto program = sourceFile->GetChild("Program");

        if (program == nullptr)
        {
            //exception
            return;
        }

        const auto main = program->FindFunction("Main", { Array::Instance(&String::Instance()) });
        if (main == nullptr)
        {
            //exception
            return;
        }

        const auto result = CreateOutputFile(outputDirectory, std::format("{}.{}", projectName, "dll"));
        if (!result)
        {
            //exception
            return;
        }

        projectLocation = *result;
        stringBuilder.PushLine(std::format(".assembly {} {}", projectName, "{}"));
        stringBuilder.PushLine(".assembly extern mscorelib");
        stringBuilder.PushLine(".assembly extern System.Runtime {}");
        stringBuilder.PushLine(".assembly extern  System.Collections.Generic.Runtime {}");


        stringBuilder.PushLine("");
        stringBuilder.PushLine("class public auto ansi beforefieldinit EntryPoint extends [mscorlib]System.Object");

        stringBuilder.PushLine(open_flower);
        stringBuilder.IncreaseIndent();

        stringBuilder.PushLine(".method public hidebysig static void Main() cil managed");

        stringBuilder.PushLine(open_flower);
        stringBuilder.IncreaseIndent();

        stringBuilder.PushLine(".entrypoint");
        stringBuilder.PushLine("maxstack 8");
        stringBuilder.PushLine(main->FullName());
        stringBuilder.PushLine("ret");

        stringBuilder.PushLine(close_flower);
        stringBuilder.IncreaseIndent();

        stringBuilder.PushLine(close_flower);
        stringBuilder.IncreaseIndent();

        PushTranscription();
    }

    const std::string& CILTranspiler::OutputFile() const { return projectLocation; }

    void CILTranspiler::Transpile()
    {
        TranspileDirectory(source);
    }

    void CILTranspiler::PushTranscription()
    {
        if (std::ofstream file(projectLocation); file.is_open())
        {
            file << stringBuilder.Value();

            file.close();
            stringBuilder.Clear();
        }
    }

    void CILTranspiler::TranspileDirectory(const SourceDirectory* const directory)
    {
        for (const auto child: directory->values())
        {
            if (child->SourceType() == SourceType::File)
                TranspileFile(dynamic_cast<const SourceFile*>(child));
            else
                TranspileDirectory(dynamic_cast<const SourceDirectory*>(child));
        }
    }

    void CILTranspiler::TranspileFile(const SourceFile* file)
    {
        for (const auto type : file->values())
            TranspileDataType(type);
    }

    void CILTranspiler::TranspileConstant(const ICharacteristic* constant)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".field {} {} {} = {}", FieldDescriberString(constant), constant->CreationType()->FullName(), constant->Name(), TranspileConstantString(constant)));
    }

    void CILTranspiler::TranspileCharacteristic(const ICharacteristic* const characteristic)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".field {} {} {}", FieldDescriberString(characteristic), characteristic->CreationType()->FullName(), characteristic->Name()));
    }

    void CILTranspiler::TranspileFunction(const IScoped* const function)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".method {} final {} {} {}({}) cil managed", AccessModifierString(function), FunctionStaticString(function), function->CreationType()->FullName(), function->Name(), FunctionParametersString(function)));
        stringBuilder.PushLine(open_flower);

        stringBuilder.IncreaseIndent();

        TranspileFunctionBody(function, "");

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);
    }

    void CILTranspiler::TranspileConstructor(const IScoped* const constructor, const string& precursor)
    {
        const auto result = FunctionVariablesString(constructor);

        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".method {} hidebysig specialname rtspecialname {} void {}({}) cil managed", AccessModifierString(constructor), FunctionStaticString(constructor), constructor->Name(), ParameterString(constructor)));
        stringBuilder.PushLine(open_flower);

        stringBuilder.IncreaseIndent();

        TranspileFunctionBody(constructor, precursor);

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);
    }

    void CILTranspiler::TranspileFunctionBody(const IScoped* const scoped, const std::string& precursor)
    {
        int maxSlotSize = 0;
        auto builder = StringBuilder();

        builder.SetIndent(stringBuilder.Indent());

        TranspileScope(scoped->Scope(), builder, maxSlotSize);

        stringBuilder.PushLine(std::format(".maxstack {}", maxSlotSize));
        stringBuilder.PushLine(std::format(".localsinit({})", FunctionVariablesString(scoped)));

        if (!precursor.empty())
            stringBuilder.PushLine(precursor);

        stringBuilder.Push(builder.Value());
    }

    void CILTranspiler::TranspileScope(const Scope* const scope, StringBuilder& stringBuilder, int& maxSlotSize)
    {
        const auto flag = scope->Type() != ScopeType::Scope;
        if (flag)
        {
            stringBuilder.PushLine(std::format("{}:", scope->FullName()));
            stringBuilder.IncreaseIndent();
        }

        for (const auto context: *scope)
        {
            TranspileContext(context, stringBuilder);
            if (const auto size = context->SlotCount(); size > maxSlotSize)
                maxSlotSize = size;
        }

        if (flag)
            stringBuilder.DecreaseIndent();

        const auto nestedCount = scope->NestedCount();
        for (int i = 0; i < nestedCount; i++)
        {
            const auto nested = scope->NestedAt(i);
            TranspileScope(nested, stringBuilder, maxSlotSize);
        }
    }

    void CILTranspiler::TranspileDataType(const IUserDefinedType* const dataType)
    {
        stringBuilder.PushLine("");
        switch (dataType->MemberType())
        {
            case MemberType::Enum:
                stringBuilder.PushLine(std::format(".class {} {} {} {} {} {} {}", AccessModifierString(dataType), prefix_sealed, prefix_auto, prefix_ansi, dataType->Name(), prefix_extends, ms_core_enum));
                break;
            case MemberType::Class:
                stringBuilder.PushLine(std::format(".class {} {} {} {} {} {} {}", AccessModifierString(dataType), DataTypeStaticString(dataType), prefix_sequential, prefix_ansi, dataType->Name(), prefix_extends, ms_core_class));
                break;
            case MemberType::ValueType:
                stringBuilder.PushLine(std::format(".class {} {} {} {} {} {} {}", AccessModifierString(dataType), DataTypeStaticString(dataType), prefix_auto, prefix_ansi, dataType->Name(), prefix_extends, ms_core_struct));
                break;
            default:
                break;
        }

        stringBuilder.PushLine(open_flower);
        stringBuilder.IncreaseIndent();

        if (dataType->MemberType() == MemberType::Enum)
            stringBuilder.PushLine(".field public specialname rtspecialname int32 value__ ");


        StringBuilder instancePrecursor, staticPrecursor;

        staticPrecursor.SetIndent(stringBuilder.Indent() + 1);
        instancePrecursor.SetIndent(stringBuilder.Indent() + 1);

        instancePrecursor.PushLine("");

        for (const auto characteristic: dataType->AllCharacteristics())
        {
            if (characteristic->MemberType() == MemberType::ConstantField)
                TranspileConstant(characteristic);
            else
            {
                TranspileCharacteristic(characteristic);

                if (characteristic->CheckDescriber(Describer::Static))
                    TranspileContext(characteristic->Context(), staticPrecursor);
                else
                    TranspileContext(characteristic->Context(), instancePrecursor);
            }
        }

        if (!staticPrecursor.Value().empty())
        {
            //push static constructor
        }

        for (const auto scoped: dataType->AllScoped())
        {
            if (scoped->MemberType() == MemberType::Constructor)
                TranspileConstructor(scoped, instancePrecursor.Value());
            else
                TranspileFunction(scoped);
        }

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);

        PushTranscription();
    }
}
