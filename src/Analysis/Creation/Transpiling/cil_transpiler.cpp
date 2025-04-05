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
#include "../../Structure/Context/Expressions/built_in_binary_expression.h"
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

constexpr string open_flower = "\n{\n";
constexpr string close_flower = "\n}\n";

constexpr string prefix_auto = "auto";
constexpr string prefix_ansi = "ansi";
constexpr string prefix_sealed = "sealed";
constexpr string prefix_extends = "extends";
constexpr string prefix_sequential = "sequential";
constexpr string prefix_before = "beforefieldinit";

constexpr string ms_core_enum = "[System.Runtime]System.Enum";
constexpr string ms_core_class = "[System.Runtime]System.Object";
constexpr string ms_core_struct = "[System.Runtime]System.TypeValue";

constexpr string pop = "pop";
constexpr string dup = "dup";
constexpr string load_this = "ldarg.0";

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

    string AccessibilityString(const IDescribable* const describer)
    {
        if (describer->CheckDescriber(Describer::Public))
            return "public";

        return "private";
    }

    string DataTypeStaticString(const IDescribable* const describer)
    {
        if (describer->CheckDescriber(Describer::Static))
            return "sealed abstract";

        return "sealed";
    }

    string FieldDescriberString(const IDescribable* const describer)
    {
        string value;
        if (describer->CheckDescriber(Describer::Static))
            value += "static";

        if (describer->CheckDescriber(Describer::Const))
            value = "literal ";
        else if (describer->CheckDescriber(Describer::Constexpr))
            value = "initonly ";

        if (!value.empty())
            value.pop_back();

        return "";
    }

    string FunctionCallConventionString(const IDescribable* const describer)
    {
        if (describer->CheckDescriber(Describer::Static))
            return "static";

        return "instance";
    }

    string FunctionParameterString(const IScoped* const function)
    {
        string value;
        for (int i = 0; i < function->ParameterCount(); i++)
        {
            const auto parameter = *function->VariableAt(i);
            value += std::format("{} {}", parameter.CreationType()->FullName(), parameter.Name());

            if (i < function->ParameterCount() - 1)
                value += ", ";
        }

        return value;
    }

    string FunctionLocalVariablesString(const IScoped* const function)
    {
        string value;
        for (auto i = function->ParameterCount(); i < function->VariableCount() + function->ParameterCount(); i++)
        {
            const auto parameter = *function->VariableAt(i);
            value += std::format("{} {}", parameter.CreationType()->FullName(), parameter.Name());

            if (i < function->ParameterCount() - 1)
                value += ", ";
        }

        return value;
    }

    void TranspileLoad(const IContextNode* context, StringBuilder& stringBuilder);
    void TranspileLoad(const IContextNode* current, const IContextNode* context, StringBuilder& stringBuilder);

    void TranspileExpression(const IContextNode* context, StringBuilder& stringBuilder);

    void TranspileLoadField(const IContextNode* const fieldContext, StringBuilder& stringBuilder, const bool loadAddress)
    {
        const auto field = reinterpret_cast<const IVariable*>(fieldContext->Metadata());
        const auto instruction = loadAddress && field->CreationType()->MemberType() != MemberType::Class ? "flda" : "fld";

        if (field->CheckDescriber(Describer::Constexpr))
        {

        }
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
        const auto field = reinterpret_cast<const IVariable*>(fieldContext->Metadata());
        const auto instruction = loadAddress && field->CreationType()->MemberType() != MemberType::Class ? "flda" : "fld";

        if (field->CheckDescriber(Describer::Constexpr))
        {

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
        stringBuilder.PushLine("ldc.i4 " + arguments->ChildCount());
        stringBuilder.PushLine(arrayType->FindConstructor({ &Integer::Instance() })->FullName());

        const auto indexerString = arrayType->FindIndexer({ &Integer::Instance() })->SignatureSetString();

        for (auto i = 0; i < arguments->ChildCount(); i++)
        {
            if (i++ < arguments->ChildCount() - 1)
                stringBuilder.PushLine(dup);

            stringBuilder.PushLine("ldc.i4 " + i++);
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
                            if (const auto field = reinterpret_cast<const IVariable*>(current->Metadata()); field->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
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
                                const auto field = reinterpret_cast<const IVariable*>(finalContext->Metadata());
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

    void TranspileExpression(const ContextNode* const context, StringBuilder& stringBuilder)
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
                                const auto field = reinterpret_cast<const IVariable*>(finalContext->Metadata());
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
    }

    const std::string& CILTranspiler::OutputFile() const { return projectLocation; }

    void CILTranspiler::Transpile()
    {
        TranspileDirectory(source);
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

    void CILTranspiler::TranspileConstant(const GlobalConstant* const constant)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".field public static literal valuetype {} {} = {}", constant->Parent()->FullName(), constant->Name(), constant->ValueString()));
    }

    void CILTranspiler::TranspileCharacteristic(const ICharacteristic* const characteristic)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".field {} {} {}", FieldDescriberString(characteristic), characteristic->CreationType()->FullName(), characteristic->Name()));
    }

    void CILTranspiler::TranspileFunction(const IScoped* const function)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".method {} final {} {} {}({}) cil managed", AccessibilityString(function), FunctionCallConventionString(function), function->CreationType()->FullName(), function->Name(), FunctionParameterString(function)));
        stringBuilder.PushLine(open_flower);

        stringBuilder.IncreaseIndent();

        TranspileFunctionBody(function);

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);
    }

    void CILTranspiler::TranspileConstructor(const IScoped* const constructor)
    {
        stringBuilder.PushLine("");
        stringBuilder.PushLine(std::format(".method {} hidebysig specialname rtspecialname {} void {}({}) cil managed", AccessibilityString(constructor), FunctionStaticDtring(scoped), constructor->Name(), ParameterString(constructor)));
        stringBuilder.PushLine(open_flower);

        stringBuilder.IncreaseIndent();

        TranspileFunctionBody(constructor);

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);
    }

    void CILTranspiler::TranspileFunctionBody(const IScoped* const scoped)
    {
        int maxSlotSize = 0;
        auto builder = StringBuilder();

        builder.SetIndent(stringBuilder.Indent());

        TranspileScope(scoped->Scope(), builder, maxSlotSize);

        stringBuilder.PushLine(std::format(".maxstack {}", maxSlotSize));
        stringBuilder.PushLine(std::format(".localsinit({})", FunctionLocalVariablesString(scoped)));

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

    void CILTranspiler::TranspileContext(const ContextNode* context, StringBuilder& stringBuilder)
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

    void CILTranspiler::TranspileDataType(const IUserDefinedType* const dataType)
    {
        stringBuilder.PushLine("");
        switch (dataType->MemberType())
        {
            case MemberType::Enum:
                stringBuilder.PushLine(std::format(".class {} {} {} {} {} {} {}", AccessibilityString(dataType), prefix_sealed, prefix_auto, prefix_ansi, dataType->Name(), prefix_extends, ms_core_enum));
                break;
            case MemberType::Class:
                stringBuilder.PushLine(std::format(".class {} {} {} {} {} {} {}", AccessibilityString(dataType), DataTypeStaticString(dataType), prefix_sequential, prefix_ansi, dataType->Name(), prefix_extends, ms_core_class));
                break;
            case MemberType::ValueType:
                stringBuilder.PushLine(std::format(".class {} {} {} {} {} {} {}", AccessibilityString(dataType), DataTypeStaticString(dataType), prefix_auto, prefix_ansi, dataType->Name(), prefix_extends, ms_core_struct));
                break;
            default:
                break;
        }

        stringBuilder.PushLine(open_flower);
        stringBuilder.IncreaseIndent();

        for (const auto characteristic: dataType->AllCharacteristics())
        {

        }

        for (const auto characteristic: dataType->AllScoped())
        {
            //create functions
        }

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);
    }
}
