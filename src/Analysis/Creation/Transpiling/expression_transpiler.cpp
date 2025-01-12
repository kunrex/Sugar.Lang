#include "cil_transpiler.h"

#include <format>

#include "../../Structure/Core/DataTypes/data_type.h"

#include "../../Structure/Nodes/Context/context_node.h"
#include "../../Structure/Nodes/Context/Casts/overloaded_cast_instruction.h"
#include "../../Structure/Nodes/Context/Entities/Functions/function_context.h"
#include "../../Structure/Nodes/Context/Entities/Functions/print.h"
#include "../../Structure/Nodes/Context/Expressions/dot_expression.h"
#include "../../Structure/Nodes/Context/Expressions/overloaded_indexer_expression.h"

using namespace Services;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Context;

//Dot
//|
//| - x
//| - y

constexpr std::string load_this = "ldarg.0";

namespace Analysis::Creation
{
    void CILTranspiler::TranspileExpression(const std::string& indent, const ContextNode* expression)
    {
        switch (expression->MemberType())
        {
            case MemberType::Dot:
            case MemberType::FieldContext:
            case MemberType::ThisContext:
            case MemberType::InputContext:
            case MemberType::PrintContext:
            case MemberType::FormatContext:
            case MemberType::FunctionCallContext:
            case MemberType::LocalVariableContext:
            case MemberType::FunctionArgumentContext:
            case MemberType::OverloadedIndexerContext:
                TranspileEntityInit(indent, expression);;
                break;
            case MemberType::Box:
            case MemberType::Unbox:
            case MemberType::CastClass:
            case MemberType::OverloadedCastContext:
                {
                    const auto casted = dynamic_cast<const OverloadedCastInstruction*>(expression);
                    TranspileExpression(indent, casted->Operand());

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
            case MemberType::UnaryContext:
                {
                    const auto casted = dynamic_cast<const UnaryContextNode*>(expression);



                    source += indent + casted->InstructionGet() + "\n";
                }
            break;
            case MemberType::BinaryContext:
                {
                    const auto casted = dynamic_cast<const BinaryContextNode*>(expression);
                    TranspileExpression(indent, casted->LHS());
                    TranspileExpression(indent, casted->RHS());

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
        }
    }

    void CILTranspiler::TranspileEntity(const std::string& indent, const ContextNode* entity)
    {
        switch (entity->MemberType())
        {
            case MemberType::FieldContext:
                source += indent + entity->InstructionGet() + "\n";
                break;
            case MemberType::FunctionCallContext:
                {
                    const auto casted = dynamic_cast<const FunctionContext*>(entity);

                    for (const auto child: *casted)
                        TranspileExpression(indent, child);

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
            case MemberType::OverloadedIndexerContext:
                {
                    const auto casted = dynamic_cast<const OverloadedIndexerExpression*>(entity);
                    TranspileEntity(indent, casted);

                    for (const auto child: *casted)
                        TranspileExpression(indent, child);

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
            default:
                //exception
                break;
        }
    }

    void CILTranspiler::TranspileEntityInit(const std::string& indent, const ContextNode* entity)
    {
        switch (entity->MemberType())
        {
            case MemberType::Dot:
                {
                    const auto casted = dynamic_cast<const DotExpression*>(entity);
                    TranspileEntityInit(indent, casted->LHS());
                    TranspileEntity(indent, casted->RHS());
                }
                break;
            case MemberType::PrintContext:
                {
                    const auto casted = dynamic_cast<const Print*>(entity);
                    TranspileEntityInit(indent, casted->GetChild(0));

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
            case MemberType::InputContext:
                source += indent + entity->InstructionGet() + "\n";
                break;
            case MemberType::FormatContext:
                {
                    const auto casted = dynamic_cast<const Print*>(entity);
                    source += std::format("{} ldc.i4.{}\n{} newarr [mscorlib]System.Object\n", indent, casted->ChildCount(), indent);

                    int i = 0;
                    for (const auto child: *casted)
                    {
                        source += std::format("{} dup\n{} ldc.i4.", indent, indent, i);

                        TranspileEntityInit(indent, child);
                        if (child->CreationType()->MemberType() != MemberType::Class)
                            source += indent + "box " + child->CreationType()->FullName() + "\n";

                        source += "stelem.ref\n";
                    }

                    source += indent + casted->InstructionGet() + "\n";
                }
            case MemberType::ThisContext:
                source += indent + load_this + "\n";
                break;
            case MemberType::LocalVariableContext:
            case MemberType::FunctionArgumentContext:
                source += indent + entity->InstructionGet() + "\n";
                break;
            case MemberType::FieldContext:
                source += indent + load_this + "\n" + indent + entity->InstructionGet() + "\n";
                break;
            case MemberType::FunctionCallContext:
                {
                    const auto casted = dynamic_cast<const FunctionContext*>(entity);
                    if (!casted->IsStatic())
                        source += indent + load_this + "\n";

                    for (const auto child: *casted)
                        TranspileExpression(indent, child);

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
            case MemberType::OverloadedIndexerContext:
                {
                    const auto casted = dynamic_cast<const OverloadedIndexerExpression*>(entity);
                    TranspileEntityInit(indent, casted);

                    for (const auto child: *casted)
                        TranspileExpression(indent, child);

                    source += indent + casted->InstructionGet() + "\n";
                }
                break;
            default:
                //exception
                break;
        }
    }
}
