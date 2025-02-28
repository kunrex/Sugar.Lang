#include "built_in_indexer_expression.h"

#include "../Entities/Functions/function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    BuiltInIndexerExpression::BuiltInIndexerExpression(const IIndexerDefinition* const indexer, const ContextNode* const operand, const bool isLoadInstruction) : UnaryContextNode(indexer->CreationType(), operand), slotCount(-1), isLoadInstruction(isLoadInstruction), indexer(indexer)
    { }

    MemberType BuiltInIndexerExpression::MemberType() const { return MemberType::BuiltInIndexer; }

    int BuiltInIndexerExpression::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    bool BuiltInIndexerExpression::Readable() const { return indexer->Readable(); }
    bool BuiltInIndexerExpression::Writable() const { return indexer->Writable() && creationType->MemberType() == MemberType::Class; }

    string BuiltInIndexerExpression::CILInstruction() const
    {
        if (isLoadInstruction)
            return indexer->SignatureGetString();

        return indexer->SignatureSetString();
    }
}
