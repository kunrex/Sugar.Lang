#include "defined_indexer_expression.h"

#include "../../../Core/DataTypes/data_type.h"

#include <format>

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    DefinedIndexerExpression::DefinedIndexerExpression(const IndexerDefinition* indexer, const ContextNode* operand) : UnaryContextNode(indexer->CreationType(), operand)
    {
        if (indexer->Readable())
        {
            readable = true;
            getInstruction = std::format("call instance {}", indexer->SignatureGetString());
        }
        else
        {
            readable = false;
            getInstruction = "";
        }

        if (indexer->Writable())
        {
            writable = true;
            setInstruction = std::format("call instance {}", indexer->SignatureGetString());
        }
        else
        {
            writable = false;
            setInstruction = "";
        }

        slotCount = 0;
    }

    MemberType DefinedIndexerExpression::MemberType() const { return MemberType::DefinedIndexerExpression; }

    bool DefinedIndexerExpression::Readable() const { return readable; }
    bool DefinedIndexerExpression::Writable() const { return writable; }

    std::string DefinedIndexerExpression::InstructionGet() const { return getInstruction; }
    std::string DefinedIndexerExpression::InstructionSet() const { return setInstruction; }

    int DefinedIndexerExpression::SlotCount() const
    {
        if (slotCount == 0)
        {
            int argCount = 0;
            for (const auto child: children)
            {
                if (const auto size = child->SlotCount(); size > slotCount - argCount)
                    slotCount = size + argCount;

                argCount += child->CreationType()->SlotCount();
                slotCount += child->CreationType()->SlotCount();
            }

            slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }
}


