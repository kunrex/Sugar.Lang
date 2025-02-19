#include "built_in_indexer_expression.h"
#include "../context_node.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    BuiltInIndexerExpression::BuiltInIndexerExpression(const IndexerDefinition* indexer, const ContextNode* operand) : UnaryContextNode(indexer->CreationType(), operand), readable(indexer->Readable()), writable(indexer->Writable()), getInstruction(indexer->SignatureGetString()), setInstruction(indexer->SignatureSetString())
    {

    }

    MemberType BuiltInIndexerExpression::MemberType() const { return MemberType::BuiltInIndexer; }

    bool BuiltInIndexerExpression::Readable() const { return readable; }
    bool BuiltInIndexerExpression::Writable() const { return writable; }

    std::string BuiltInIndexerExpression::InstructionGet() const { return getInstruction; }
    std::string BuiltInIndexerExpression::InstructionSet() const { return setInstruction; }

    int BuiltInIndexerExpression::SlotCount() const
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
