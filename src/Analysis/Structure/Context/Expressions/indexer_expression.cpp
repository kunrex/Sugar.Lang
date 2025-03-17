#include "indexer_expression.h"

#include <format>

#include "../Entities/Functions/function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    IndexerExpression::IndexerExpression(const IIndexerDefinition* const indexer, const ContextNode* const operand) : UnaryContextNode(indexer->CreationType(), operand), slotCount(-1), indexer(indexer)
    { }

    MemberType IndexerExpression::MemberType() const { return MemberType::IndexerExpression; }

    int IndexerExpression::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    bool IndexerExpression::Readable() const { return indexer->Readable(); }
    bool IndexerExpression::Writable() const { return indexer->Writable() && creationType->MemberType() == MemberType::Class; }

    string IndexerExpression::CILData() const { return ""; }

    const IIndexerDefinition* IndexerExpression::Indexer() const { return indexer; }
}


