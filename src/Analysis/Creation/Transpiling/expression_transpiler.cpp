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
    void CILTranspiler::TranspileExpression(const ContextNode* expression)
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
                TranspileEntityInit(expression);
                break;
            case MemberType::Box:
            case MemberType::Unbox:
            case MemberType::CastClass:
            case MemberType::OverloadedCastContext:
                {
                    const auto casted = dynamic_cast<const OverloadedCastInstruction*>(expression);
                    TranspileExpression(casted->Operand());

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
            case MemberType::UnaryContext:
                {
                    const auto casted = dynamic_cast<const UnaryContextNode*>(expression);



                    stringBuilder.PushLine(casted->InstructionGet());
                }
            break;
            case MemberType::BinaryContext:
                {
                    const auto casted = dynamic_cast<const BinaryContextNode*>(expression);
                    TranspileExpression(casted->LHS());
                    TranspileExpression(casted->RHS());

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
        }
    }

    void CILTranspiler::TranspileEntity(const ContextNode* entity)
    {
        switch (entity->MemberType())
        {
            case MemberType::FieldContext:
                stringBuilder.PushLine(entity->InstructionGet());
                break;
            case MemberType::FunctionCallContext:
                {
                    const auto casted = dynamic_cast<const FunctionContext*>(entity);

                    for (const auto child: *casted)
                        TranspileExpression(child);

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
            case MemberType::OverloadedIndexerContext:
                {
                    const auto casted = dynamic_cast<const OverloadedIndexerExpression*>(entity);
                    TranspileEntity(casted);

                    for (const auto child: *casted)
                        TranspileExpression(child);

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
            default:
                //exception
                break;
        }
    }

    void CILTranspiler::TranspileEntityInit(const ContextNode* entity)
    {
        switch (entity->MemberType())
        {
            case MemberType::Dot:
                {
                    const auto casted = dynamic_cast<const DotExpression*>(entity);
                    TranspileEntityInit(casted->LHS());
                    TranspileEntity(casted->RHS());
                }
                break;
            case MemberType::PrintContext:
                {
                    const auto casted = dynamic_cast<const Print*>(entity);
                    TranspileEntityInit(casted->GetChild(0));

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
            case MemberType::InputContext:
                stringBuilder.PushLine(entity->InstructionGet());
                break;
            case MemberType::FormatContext:
                {
                    const auto casted = dynamic_cast<const Print*>(entity);
                    stringBuilder.PushLine("ldc.i4." + casted->ChildCount());
                    stringBuilder.PushLine("newarr [mscorlib]System.Object");

                    int i = 0;
                    for (const auto child: *casted)
                    {
                        stringBuilder.PushLine("dup");
                        stringBuilder.PushLine(" ldc.i4." + i);

                        TranspileEntityInit(child);
                        if (child->CreationType()->MemberType() != MemberType::Class)
                            stringBuilder.PushLine("box " + child->CreationType()->FullName());

                        stringBuilder.PushLine("stelem.ref");
                    }

                    stringBuilder.PushLine("casted->InstructionGet()");
                }
            case MemberType::ThisContext:
                stringBuilder.PushLine(load_this);
                break;
            case MemberType::LocalVariableContext:
            case MemberType::FunctionArgumentContext:
                stringBuilder.PushLine(entity->InstructionGet());
                break;
            case MemberType::FieldContext:
                stringBuilder.PushLine(load_this);
                stringBuilder.PushLine(entity->InstructionGet());
                break;
            case MemberType::FunctionCallContext:
                {
                    const auto casted = dynamic_cast<const FunctionContext*>(entity);
                    if (!casted->IsStatic())
                        stringBuilder.PushLine(load_this);

                    for (const auto child: *casted)
                        TranspileExpression(child);

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
            case MemberType::OverloadedIndexerContext:
                {
                    const auto casted = dynamic_cast<const OverloadedIndexerExpression*>(entity);
                    TranspileEntityInit(casted);

                    for (const auto child: *casted)
                        TranspileExpression(child);

                    stringBuilder.PushLine(casted->InstructionGet());
                }
                break;
            default:
                //exception
                break;
        }
    }
}
