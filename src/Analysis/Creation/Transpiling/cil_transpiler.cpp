#include "cil_transpiler.h"

#include <format>
#include <fstream>
#include <filesystem>

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/transpile_file_exception.h"
#include "../../Structure/Context/Entities/this_context.h"
#include "../../Structure/Context/Entities/Functions/function_call_context.h"
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

using namespace std;
namespace fs = filesystem;

using namespace Services;

using namespace Exceptions;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Core::Interfaces;

constexpr string open_flower = "\n{\n\t";
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

    void CILTranspiler::TranspileLoadInstruction(const ContextNode* const load, StringBuilder& stringBuilder)
    {
        switch (load->MemberType())
        {
            case MemberType::LocalVariableContext:
                {
                    if (const auto localVariable = dynamic_cast<const LocalVariableContext*>(load); localVariable->CreationType()->MemberType() == MemberType::Class)
                        stringBuilder.PushLine("ldloc." + localVariable->Index());
                    else
                        stringBuilder.PushLine("ldloca." + localVariable->Index());
                }
                break;
            case MemberType::FunctionParameterContext:
                {
                    if (const auto parameter = dynamic_cast<const ParameterContext*>(load); parameter->CreationType()->MemberType() == MemberType::Class)
                        stringBuilder.PushLine("ldarg." + parameter->Index());
                    else
                        stringBuilder.PushLine("ldarga." + parameter->Index());
                }
                break;
            case MemberType::FieldContext:
                stringBuilder.PushLine(load->CILData());
                break;
            case MemberType::PropertyContext:
                {
                    const auto property = dynamic_cast<const PropertyContext*>(load)->Property();
                    stringBuilder.PushLine(property->SignatureGetString());
                }
                break;
            default:
                break;
        }
    }

    void CILTranspiler::TranspileDotLHS(const ContextNode* const lhs, StringBuilder& stringBuilder)
    {
        switch (lhs->MemberType())
        {
            case MemberType::StaticReferenceContext:
                break;
            case MemberType::ThisContext:
                stringBuilder.PushLine(lhs->CILData());
                break;
            case MemberType::FieldContext:
            case MemberType::PropertyContext:
            case MemberType::LocalVariableContext:
            case MemberType::FunctionParameterContext:
                TranspileLoadInstruction(lhs, stringBuilder);
                break;
            case MemberType::FunctionCallContext:
                {
                    const auto function = *dynamic_cast<const FunctionCallContext*>(lhs);
                    for (const auto argument: function)
                        stringBuilder.PushLine(TranspileExpression(argument, stringBuilder));

                    stringBuilder.PushLine(function.CILData());
                }
            case MemberType::IndexerExpression:
                {
                    const auto indexer = *dynamic_cast<const IndexerExpression*>(lhs);
                    TranspileDotLHS(indexer.Operand(), stringBuilder);

                    for (const auto argument: indexer)
                        stringBuilder.PushLine(TranspileExpression(argument, stringBuilder));

                    stringBuilder.Push(indexer.Indexer()->SignatureGetString());
                }
            default:
                break;
        }
    }

    void CILTranspiler::TranspileDotEnd(const ContextNode* const rhs, StringBuilder& stringBuilder)
    {
        switch (rhs->MemberType())
        {

        }
    }

    void CILTranspiler::TranspileContext(const ContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case MemberType::Dot:
                {
                    const auto dotContext = dynamic_cast<const DotExpression*>(context);
                    TranspileDotLHS(dotContext->LHS(), stringBuilder);

                    const auto rhs = dotContext->RHS();
                    if (rhs->MemberType() == MemberType::Dot)
                        TranspileContext(rhs, stringBuilder);


                }
                break;
            case MemberType::
        }
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

    void CILTranspiler::TranspileEntity(const ContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case
        }
    }

    void CILTranspiler::TranspileExpression(const ContextNode* const context, StringBuilder& stringBuilder)
    {

    }

    void CILTranspiler::TranspileAssignment(const AssignmentExpression* const assignment, StringBuilder& stringBuilder, const bool leaveCopy)
    {
        const auto lhs = assignment->LHS();

        string instruction;
        switch (lhs->MemberType())
        {
            case MemberType::Dot:
                {
                    const auto dot = dynamic_cast<const DotExpression*>(lhs);
                    TranspileDotLHS(dot->LHS(), stringBuilder);
                    const auto rhs = dot->RHS();
                    if (rhs->MemberType() == MemberType::Dot)

                }
                break;
            case MemberType::FieldContext:
                {
                    const auto field = dynamic_cast<const FieldContext*>(lhs)->Variable();
                    stringBuilder.PushLine("ldarg.0");
                    instruction = std::format("stfld {} {}", field->CreationType()->FullName(), field->FullName());
                }
                break;
            case MemberType::PropertyContext:
                {
                    const auto propertyContext = dynamic_cast<const PropertyContext*>(lhs);
                    stringBuilder.PushLine("ldarg.0");
                    instruction = propertyContext->Property()->SignatureSetString();
                }
                break;
            case MemberType::LocalVariableContext:
                {
                    const auto variableContext = dynamic_cast<const LocalVariableContext*>(lhs);
                    instruction = "stloc." + variableContext->Index();
                }
                break;
            case MemberType::FunctionParameterContext:
                {
                    const auto parameterContext = dynamic_cast<const ParameterContext*>(lhs);
                    instruction = "starg." + parameterContext->Index();
                }
                break;
            case MemberType::IndexerExpression:
                {
                    const auto indexerExpression = *dynamic_cast<const IndexerExpression*>(lhs);
                    for (const auto argument: indexerExpression)
                        TranspileExpression(argument, stringBuilder);

                    TranspileLoadInstruction(indexerExpression.Operand(), stringBuilder);
                    instruction = indexerExpression.Indexer()->SignatureSetString();
                }
                break;
            default:
                break;
        }

        TranspileExpression(assignment->RHS(), stringBuilder);

        if (leaveCopy)
            stringBuilder.PushLine("dup");

        stringBuilder.PushLine(instruction);
    }

    void CILTranspiler::TranspileDataType(const Interfaces::IUserDefinedType* const dataType)
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
