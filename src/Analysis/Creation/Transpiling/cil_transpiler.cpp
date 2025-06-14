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
#include "../../Structure/Context/Expressions/duplicate_expression.h"
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

namespace Analysis::Creation::Transpiling
{
    std::string_view AccessModifierString(const IDescribable* const describable) { return describable->CheckDescriber(Describer::Public) ? "public" : "private"; }

    std::string_view StaticModifierString(const IFunction* const describable) { return describable->CheckDescriber(Describer::Static) ? "static" : "instance"; }
    std::string_view StaticModifierString(const IUserDefinedType* const describable) { return describable->CheckDescriber(Describer::Static) ? "sealed abstract" : "sealed"; }

    string ConstantString(const ICharacteristic* const characteristic)
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
                return *reinterpret_cast<const string*>(characteristic->Context()->Metadata());
            default:
                return "";
        }
    }

    string ScopedParameterString(const IScoped* const function)
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

    string ScopedLocalVariableString(const IScoped* const function)
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

    void TranspileLoad(const IContextNode* context, StringBuilder& stringBuilder);
    void TranspileLoad(const IContextNode* current, const IContextNode* context, StringBuilder& stringBuilder);

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
        TranspileLoadArguments(functionCallContext, 0, stringBuilder);
        if (const auto function = reinterpret_cast<const IFunctionDefinition*>(functionCallContext->Metadata()); !function->CheckDescriber(Describer::Static))
            stringBuilder.PushLine(load_this);

        stringBuilder.PushLine(functionCallContext->CILData());
    }

    void TranspileFunctionCall(const IContextNode* const functionCallContext, const IContextNode* const context, StringBuilder& stringBuilder)
    {
        TranspileLoadArguments(functionCallContext, 0, stringBuilder);
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
        stringBuilder.PushLine(arrayType->FindConstructor({ Integer::Instance() })->FullName());

        const auto indexerString = arrayType->FindIndexer({ Integer::Instance() })->SignatureSetString();

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
            case MemberType::InputContext:
            case MemberType::ConstantContext:
                stringBuilder.PushLine(context->CILData());
                break;
            case MemberType::PrintContext:
                {
                    if (const auto value = context->GetChild(static_cast<int>(ChildCode::Expression)); value != nullptr)
                        TranspileExpression(value, stringBuilder);

                    stringBuilder.PushLine(context->CILData());
                }
                break;
            case MemberType::FormatContext:
                {
                    for (auto i = 0; i < context->ChildCount(); i++)
                        TranspileExpression(context->GetChild(i), stringBuilder);

                    stringBuilder.PushLine(context->CILData());
                }
                break;
            case MemberType::FormatSingleContext:
                {
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::RHS)), stringBuilder);
                    stringBuilder.PushLine(context->CILData());
                }
                break;
            case MemberType::FormatDoubleContext:
                {
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::Expression)), stringBuilder);
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::RHS)), stringBuilder);
                    stringBuilder.PushLine(context->CILData());
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

    void TranspileReferenceAssignment(const IDataType* const assignedType, StringBuilder& stringBuilder)
    {
        switch (assignedType->Type())
        {
            case TypeKind::Short:
                stringBuilder.PushLine("stind.i2");
                break;
            case TypeKind::Int:
            case TypeKind::Boolean:
            case TypeKind::Character:
                stringBuilder.PushLine("stind.i4");
                break;
            case TypeKind::Long:
                stringBuilder.PushLine("stind.i8");
                break;
            case TypeKind::Float:
                stringBuilder.PushLine("stind.r4");
                break;
            case TypeKind::Double:
                stringBuilder.PushLine("stind.r8");
                break;
            default:
                stringBuilder.PushLine(std::format("cpobj {}", assignedType->FullName()));
                break;
        }
    }

    void TranspileExpression(const IContextNode* const context, StringBuilder& stringBuilder)
    {
        switch (context->MemberType())
        {
            case MemberType::CastExpression:
            case MemberType::UnaryExpression:
            case MemberType::DuplicateExpression:
                {
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::Expression)), stringBuilder);
                    stringBuilder.PushLine(context->CILData());
                }
                break;
            case MemberType::BinaryExpression:
                {
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::LHS)), stringBuilder);
                    TranspileExpression(context->GetChild(static_cast<int>(ChildCode::RHS)), stringBuilder);
                    stringBuilder.PushLine(context->CILData());
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
                            {
                                if (finalContext->CreationType()->Type() == TypeKind::Referenced)
                                {
                                    stringBuilder.PushLine("ldloc." + finalContext->CILData());
                                    TranspileReferenceAssignment(rhs->CreationType(), stringBuilder);
                                }
                                else
                                    stringBuilder.PushLine("stloc." + finalContext->CILData());
                            }
                            break;
                        case MemberType::FunctionParameterContext:
                            {
                                if (finalContext->CreationType()->Type() == TypeKind::Referenced)
                                {
                                    stringBuilder.PushLine("ldarg." + finalContext->CILData());
                                    TranspileReferenceAssignment(rhs->CreationType(), stringBuilder);
                                }
                                else
                                    stringBuilder.PushLine("starg." + finalContext->CILData());
                            }
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

    void TranspileScope(const Scope* const scope, StringBuilder& stringBuilder, int& maxSlotSize)
    {
        const auto flag = scope->Type() != ScopeType::Scope;
        if (flag)
        {
            stringBuilder.PushLine(std::format("{}:", scope->FullName()));
            stringBuilder.IncreaseIndent();
        }

        const auto contextCount = scope->ChildCount();
        for (auto i = 0; i < contextCount; i++)
        {
            const auto current = scope->GetChild(i);

            TranspileContext(current, stringBuilder);
            if (const auto size = current->SlotCount(); size > maxSlotSize)
                maxSlotSize = size;
        }

        if (flag)
            stringBuilder.DecreaseIndent();

        const auto nestedCount = scope->NestedCount();
        for (auto i = 0; i < nestedCount; i++)
        {
            const auto nested = scope->NestedAt(i);
            TranspileScope(nested, stringBuilder, maxSlotSize);
        }
    }
}
