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
#include "../../Structure/Wrappers/Reference/void.h"
#include "../../Structure/Wrappers/Value/integer.h"

using namespace std;
namespace fs = filesystem;

using namespace Services;

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Wrappers;
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

    void TranspileLoad(const ContextNode* context, StringBuilder& stringBuilder);
    void TranspileLoad(const ContextNode* current, const ContextNode* context, StringBuilder& stringBuilder);

    void TranspileExpression(const ContextNode* context, StringBuilder& stringBuilder);

    void TranspileLoadField(const FieldContext* const fieldContext, StringBuilder& stringBuilder, const bool loadAddress)
    {
        const auto field = fieldContext->Variable();
        const auto instruction = loadAddress && field->CreationType()->MemberType() != MemberType::Class ? "flda" : "fld";

        if (field->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(std::format("lds{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
        else
        {
            stringBuilder.PushLine(load_this);
            stringBuilder.PushLine(std::format("ld{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
        }
    }

    void TranspileLoadField(const FieldContext* const fieldContext, const ContextNode* const context, StringBuilder& stringBuilder, bool loadAddress)
    {
        const auto field = fieldContext->Variable();
        const auto instruction = loadAddress && field->CreationType()->MemberType() != MemberType::Class ? "flda" : "fld";

        if (field->CheckDescriber(Describer::Static))
        {
            if (context->MemberType() != MemberType::StaticReferenceContext)
                stringBuilder.PushLine(pop);

            stringBuilder.PushLine(std::format("lds{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
        }
        else
            stringBuilder.PushLine(std::format("ld{} {} {}", instruction, field->CreationType()->FullName(), field->FullName()));
    }

    void TranspileLoadProperty(const PropertyContext* const propertyContext, StringBuilder& stringBuilder)
    {
        const auto property = propertyContext->Property();
        if (!property->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(load_this);

        stringBuilder.PushLine(property->SignatureGetString());
    }

    void TranspileLoadProperty(const PropertyContext* const propertyContext, const ContextNode* const context, StringBuilder& stringBuilder)
    {
        const auto property = propertyContext->Property();

        if (property->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
            stringBuilder.PushLine(pop);

        stringBuilder.PushLine(property->SignatureGetString());
    }

    void TranspileLoadArguments(const ConstantCollection<ContextNode>& arguments, StringBuilder& stringBuilder)
    {
        for (const auto argument: arguments)
            TranspileExpression(argument, stringBuilder);
    }

    void TranspileFunctionCall(const FunctionCallContext& functionCallContext, StringBuilder& stringBuilder)
    {
        TranspileLoadArguments(functionCallContext, stringBuilder);
        if (!functionCallContext.Function()->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(load_this);

        stringBuilder.PushLine(functionCallContext.CILData());
    }

    void TranspileFunctionCall(const FunctionCallContext& functionCallContext, const ContextNode* const context, StringBuilder& stringBuilder)
    {
        if (functionCallContext.Function()->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
            stringBuilder.PushLine(pop);

        stringBuilder.PushLine(functionCallContext.CILData());
    }

    void TranspileIndexerExpression(const IndexerExpression& indexerExpression, StringBuilder& stringBuilder)
    {
        TranspileLoad(indexerExpression.Operand(), stringBuilder);
        TranspileLoadArguments(indexerExpression, stringBuilder);

        stringBuilder.PushLine(indexerExpression.Indexer()->SignatureGetString());
    }

    void TranspileIndexerExpression(const IndexerExpression& indexerExpression, const ContextNode* const context, StringBuilder& stringBuilder)
    {
        TranspileLoad(indexerExpression.Operand(), context, stringBuilder);
        TranspileLoadArguments(indexerExpression, stringBuilder);

        stringBuilder.PushLine(indexerExpression.Indexer()->SignatureGetString());
    }

    void TranspileLoadDotLHS(const ContextNode* const lhs, const ContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (lhs->MemberType())
        {
            case MemberType::FieldContext:
                TranspileLoadField(dynamic_cast<const FieldContext*>(lhs), context, stringBuilder, true);
                break;
            case MemberType::PropertyContext:
                TranspileLoadProperty(dynamic_cast<const PropertyContext*>(lhs), context, stringBuilder);
                break;
            case MemberType::FunctionCallContext:
                TranspileFunctionCall(*dynamic_cast<const FunctionCallContext*>(lhs), context, stringBuilder);
                break;
            case MemberType::IndexerExpression:
                TranspileIndexerExpression(*dynamic_cast<const IndexerExpression*>(lhs), context, stringBuilder);
                break;
            default:
                break;
        }
    }

    void TranspileLoadDotLHS(const ContextNode* const lhs, StringBuilder& stringBuilder)
    {
        switch (lhs->MemberType())
        {
            case MemberType::FieldContext:
                TranspileLoadField(dynamic_cast<const FieldContext*>(lhs), stringBuilder, true);
                break;
            case MemberType::PropertyContext:
                TranspileLoadProperty(dynamic_cast<const PropertyContext*>(lhs), stringBuilder);
                break;
            case MemberType::LocalVariableContext:
                {
                    if (const auto localVariableContext = dynamic_cast<const LocalVariableContext*>(lhs); localVariableContext->Variable()->CreationType()->MemberType() == MemberType::Class)
                        stringBuilder.PushLine("ldloc." + dynamic_cast<const LocalVariableContext*>(lhs)->Index());
                    else
                        stringBuilder.PushLine("ldloca." + dynamic_cast<const LocalVariableContext*>(lhs)->Index());
                }
                break;
            case MemberType::FunctionParameterContext:
                {
                    if (const auto parameterContext = dynamic_cast<const ParameterContext*>(lhs); parameterContext->Variable()->CreationType()->MemberType() == MemberType::Class)
                        stringBuilder.PushLine("ldarg." + dynamic_cast<const LocalVariableContext*>(lhs)->Index());
                    else
                        stringBuilder.PushLine("ldarga." + dynamic_cast<const LocalVariableContext*>(lhs)->Index());
                }
                break;
            case MemberType::FunctionCallContext:
                TranspileFunctionCall(*dynamic_cast<const FunctionCallContext*>(lhs), stringBuilder);
                break;
            case MemberType::IndexerExpression:
                TranspileIndexerExpression(*dynamic_cast<const IndexerExpression*>(lhs), stringBuilder);
                break;
            default:
                TranspileLoad(lhs, stringBuilder);
        }
    }

    void TranspileLoad(const ContextNode* const current, const ContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (current->MemberType())
        {
            case MemberType::DotExpression:
                {
                    const auto dotExpression = dynamic_cast<const DotExpression*>(current);
                    TranspileLoadDotLHS(dotExpression->LHS(), context, stringBuilder);
                    TranspileLoad(dotExpression->RHS(), dotExpression->LHS(), stringBuilder);
                }
            case MemberType::FieldContext:
                TranspileLoadField(dynamic_cast<const FieldContext*>(current), context, stringBuilder, false);
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

    void TranspileListCollection(const IDataType* const listType, const ConstantCollection<ContextNode>* const arguments, StringBuilder& stringBuilder)
    {
        stringBuilder.PushLine(listType->FindConstructor({ })->FullName());
        if (arguments->ChildCount() == 0)
            return;

        const auto addString = listType->FindFunction("Add", { arguments->GetChild(0)->CreationType() })->FullName();

        auto i = 0;
        for (const auto argument: arguments)
        {
            if (i++ < arguments->ChildCount() - 1)
                stringBuilder.PushLine(dup);

            TranspileExpression(argument, stringBuilder);
            stringBuilder.PushLine(addString);
        }
    }

    void TranspileArrayCollection(const IDataType* const arrayType, const ConstantCollection<ContextNode>* const arguments, StringBuilder& stringBuilder)
    {
        stringBuilder.PushLine("ldc.i4 " + arguments->ChildCount());
        stringBuilder.PushLine(arrayType->FindConstructor({ &Integer::Instance() })->FullName());

        const auto indexerString = arrayType->FindIndexer({ &Integer::Instance() })->SignatureSetString();

        auto i = 0;
        for (const auto argument: *arguments)
        {
            if (i < arguments->ChildCount() - 1)
                stringBuilder.PushLine(dup);

            stringBuilder.PushLine("ldc.i4 " + i++);
            TranspileExpression(argument, stringBuilder);
            stringBuilder.PushLine(indexerString);
        }
    }

    const ContextNode* TranspileReturnLoad(const ContextNode* const initialContext, StringBuilder& stringBuilder)
    {
        if (initialContext->MemberType() == MemberType::DotExpression)
        {
            const auto initial = dynamic_cast<const DotExpression*>(initialContext);
            TranspileLoad(initial->LHS(), stringBuilder);

            auto context = initial->LHS();
            auto current = initial->RHS();
            while (true)
            {
                switch (current->MemberType())
                {
                    case MemberType::DotExpression:
                        {
                            const auto dotExpression = dynamic_cast<const DotExpression*>(current);
                            TranspileLoad(dotExpression->LHS(), context, stringBuilder);

                            context = dotExpression->LHS();
                            current = dotExpression->RHS();
                        }
                        continue;
                    case MemberType::IndexerExpression:
                        TranspileLoad(dynamic_cast<const IndexerExpression*>(current)->Operand(), context, stringBuilder);
                        break;
                    case MemberType::FieldContext:
                        {
                            if (const auto field = dynamic_cast<const FieldContext*>(current)->Variable(); field->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
                                stringBuilder.PushLine(pop);
                        }
                        break;
                    case MemberType::PropertyContext:
                        {
                            if (const auto property = dynamic_cast<const PropertyContext*>(current)->Property(); property->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
                                stringBuilder.PushLine(pop);
                        }
                        break;
                    case MemberType::FunctionCallContext:
                        {
                            if (const auto function = dynamic_cast<const FunctionCallContext*>(current)->Function(); function->CheckDescriber(Describer::Static) && context->MemberType() != MemberType::StaticReferenceContext)
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

    void TranspileLoad(const ContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case MemberType::DotExpression:
                {
                    const auto dotExpression = dynamic_cast<const DotExpression*>(context);
                    TranspileLoadDotLHS(dotExpression->LHS(), stringBuilder);
                    TranspileLoad(dotExpression->RHS(), dotExpression->LHS(), stringBuilder);
                }
            case MemberType::FieldContext:
                TranspileLoadField(dynamic_cast<const FieldContext*>(context), stringBuilder, false);
                break;
            case MemberType::PropertyContext:
                TranspileLoadProperty(dynamic_cast<const PropertyContext*>(context), stringBuilder);
                break;
            case MemberType::LocalVariableContext:
                stringBuilder.PushLine("ldloc." + dynamic_cast<const LocalVariableContext*>(context)->Index());
                break;
            case MemberType::FunctionParameterContext:
                stringBuilder.PushLine("ldarg." + dynamic_cast<const ParameterContext*>(context)->Index());
                break;
            case MemberType::FunctionCallContext:
                TranspileFunctionCall(*dynamic_cast<const FunctionCallContext*>(context), stringBuilder);
                break;
            case MemberType::IndexerExpression:
                TranspileIndexerExpression(*dynamic_cast<const IndexerExpression*>(context), stringBuilder);
                break;
            case MemberType::PrintContext:
            case MemberType::InputContext:
            case MemberType::ConstantContext:
                stringBuilder.PushLine(context->CILData());
            case MemberType::FormatContext:
                {
                    const auto formatContext = *dynamic_cast<const FormatContext*>(context);
                    for (const auto argument: formatContext)
                    {
                        TranspileExpression(argument, stringBuilder);

                        if (argument->MemberType() != MemberType::Class)
                            stringBuilder.PushLine(std::format("box {}", argument->CreationType()->FullName()));
                    }

                    stringBuilder.Push(formatContext.CILData());
                }
                break;
            case MemberType::FormatSingleContext:
                {
                    const auto operand = dynamic_cast<const FormatSingleContext*>(context)->Operand();
                    TranspileExpression(operand, stringBuilder);
                    if (operand->CreationType()->MemberType() != MemberType::Class)
                        stringBuilder.PushLine(std::format("box {}", operand->CreationType()->FullName()));

                    stringBuilder.Push(context->CILData());
                }
                break;
            case MemberType::FormatDoubleContext:
                {
                    const auto formatContext = *dynamic_cast<const FormatDoubleContext*>(context);
                    const auto lhs = formatContext.LHS(), rhs = formatContext.RHS();

                    TranspileExpression(lhs, stringBuilder);
                    if (lhs->CreationType()->MemberType() != MemberType::Class)
                        stringBuilder.PushLine(std::format("box {}", lhs->CreationType()->FullName()));

                    TranspileExpression(rhs, stringBuilder);
                    if (rhs->CreationType()->MemberType() != MemberType::Class)
                        stringBuilder.PushLine(std::format("box {}", rhs->CreationType()->FullName()));

                    stringBuilder.Push(formatContext.CILData());
                }
                break;
            case MemberType::InvokeContext:
                {
                    const auto invokeContext = *dynamic_cast<const InvokeContext*>(context);
                    TranspileLoadArguments(invokeContext, stringBuilder);

                    stringBuilder.PushLine(invokeContext.CILData());
                }
                break;
            case MemberType::FuncRefContext:
                {
                    const auto funcRefContext = dynamic_cast<const FuncRefContext*>(context);
                    if (const auto operand = funcRefContext->Operand(); operand->MemberType() != MemberType::StaticReferenceContext)
                        TranspileLoad(operand, stringBuilder);

                    stringBuilder.Push(funcRefContext->CILData());
                }
                break;
            case MemberType::CollectorConstructorCallContext:
                {
                    if (context->CreationType()->Type() == TypeKind::List)
                        return TranspileListCollection(context->CreationType(), dynamic_cast<const CollectionCreationContext*>(context), stringBuilder);

                    return TranspileArrayCollection(context->CreationType(), dynamic_cast<const CollectionCreationContext*>(context), stringBuilder);
                }
                break;
            case MemberType::RefContext:
                {
                    const auto refContext = dynamic_cast<const RefContext*>(context);

                    switch (const auto finalContext = TranspileReturnLoad(refContext->Operand(), stringBuilder); finalContext->MemberType())
                    {
                        case MemberType::FieldContext:
                            {
                                if (const auto field = dynamic_cast<const FieldContext*>(finalContext)->Variable(); field->CheckDescriber(Describer::Static))
                                    stringBuilder.PushLine(std::format("ldsflda {} {}", field->CreationType()->FullName(), field->FullName()));
                                else
                                    stringBuilder.PushLine(std::format("ldflda {} {}", field->CreationType()->FullName(), field->FullName()));
                            }
                            break;
                        case MemberType::LocalVariableContext:
                            stringBuilder.PushLine("ldloca." + dynamic_cast<const LocalVariableContext*>(finalContext)->Index());
                            break;
                        case MemberType::FunctionParameterContext:
                            stringBuilder.PushLine("ldlarga." + dynamic_cast<const ParameterContext*>(finalContext)->Index());
                            break;
                        default:
                            break;
                    }
                }
                break;
            case MemberType::CopyContext:
                {
                    const auto copyContext = dynamic_cast<const CopyContext*>(context);
                    const auto operand = copyContext->Operand();

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
                    TranspileExpression(unaryExpression->Operand(), stringBuilder);
                    stringBuilder.PushLine(unaryExpression->CILData());
                }
                break;
            case MemberType::BinaryExpression:
                {
                    const auto binaryExpression = dynamic_cast<const BinaryContextNode*>(context);
                    TranspileExpression(binaryExpression->LHS(), stringBuilder);
                    TranspileExpression(binaryExpression->RHS(), stringBuilder);
                    stringBuilder.PushLine(binaryExpression->CILData());
                }
                break;
            case MemberType::AssignmentExpression:
                {
                    const auto assignmentExpression = dynamic_cast<const BinaryContextNode*>(context);
                    const auto finalContext = TranspileReturnLoad(assignmentExpression->LHS(), stringBuilder);

                    if (finalContext->MemberType() == MemberType::IndexerExpression)
                    {
                        const auto indexerExpression = *dynamic_cast<const IndexerExpression*>(finalContext);
                        TranspileLoadArguments(indexerExpression, stringBuilder);

                        TranspileExpression(assignmentExpression->RHS(), stringBuilder);
                        stringBuilder.PushLine(indexerExpression.Indexer()->SignatureSetString());
                        break;
                    }

                    TranspileExpression(assignmentExpression->RHS(), stringBuilder);

                    stringBuilder.PushLine(dup);

                    switch (finalContext->MemberType())
                    {
                        case MemberType::FieldContext:
                            {
                                if (const auto field = dynamic_cast<const FieldContext*>(finalContext)->Variable(); field->CheckDescriber(Describer::Static))
                                    stringBuilder.PushLine(std::format("stsfld {} {}", field->CreationType()->FullName(), field->FullName()));
                                else
                                    stringBuilder.PushLine(std::format("stfld {} {}", field->CreationType()->FullName(), field->FullName()));
                            }
                            break;
                        case MemberType::PropertyContext:
                            stringBuilder.PushLine(dynamic_cast<const PropertyContext*>(finalContext)->Property()->SignatureSetString());
                            break;
                        case MemberType::LocalVariableContext:
                            stringBuilder.PushLine("stloc." + dynamic_cast<const LocalVariableContext*>(finalContext)->Index());
                            break;
                        case MemberType::FunctionParameterContext:
                            stringBuilder.PushLine("starg." + dynamic_cast<const ParameterContext*>(finalContext)->Index());
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

    CILTranspiler::CILTranspiler(string name, string directory, const SourceDirectory* const source) : projectName(std::move(name)), projectDirectory(std::move(directory)), source(source), stringBuilder()
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

        std::string outputFile;
        if (const auto programSource = source->GetChild("program"); programSource != nullptr)
        {
            const auto sourceFile = dynamic_cast<const SourceFile*>(programSource);

            if (const auto programFile = sourceFile->GetChild("Program"); programFile != nullptr)
            {
                if (const auto main = programFile->FindFunction("Main", { }); main != nullptr && main->CheckDescriber(Describer::PublicStatic))
                {
                    outputFile = std::format("{}.{}", projectName, "exe");
                }
            }
        }

        if (outputFile.empty())
            outputFile = std::format("{}.{}", projectName, "dll");

        if (const auto result = CreateOutputFile(outputDirectory, outputFile); result)
            stringBuilder = new StringBuilder(*result);
    }


    void CILTranspiler::Transpile() const
    {
        if (isExecutable)
        {
            //map program
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

    void CILTranspiler::TranspileConstant(const GlobalConstant* const constant)
    {
        stringBuilder.PushLine(std::format(".field public static literal valuetype {} {} = {}", constant->Parent()->FullName(), constant->Name(), constant->ValueString()));
    }

    void CILTranspiler::TranspileCharacteristic(const ICharacteristic* const characteristic)
    {
        stringBuilder.PushLine(std::format(".field {} {} {}", FieldDescriberString(characteristic), characteristic->CreationType()->FullName(), characteristic->Name()));
    }

    void CILTranspiler::TranspileFunction(const IScoped* const function)
    {
        stringBuilder.PushLine(std::format(".method {} final {} {} {}({}) cil managed", AccessibilityString(function), FunctionCallConventionString(function), function->CreationType()->FullName(), function->Name(), FunctionParameterString(function)));
        stringBuilder.PushLine(open_flower);

        stringBuilder.IncreaseIndent();

        TranspileFunctionBody(function);

        stringBuilder.DecreaseIndent();
        stringBuilder.PushLine(close_flower);
    }

    void CILTranspiler::TranspileConstructor(const IScoped* const constructor)
    {
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
                    stringBuilder.PushLine(pop);
                }
                break;
        }
    }

    void CILTranspiler::TranspileDataType(const IUserDefinedType* const dataType)
    {
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
