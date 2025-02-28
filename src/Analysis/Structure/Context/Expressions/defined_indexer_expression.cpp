#include "defined_indexer_expression.h"

#include <format>

#include "../Entities/Functions/function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    DefinedIndexerExpression::DefinedIndexerExpression(const IIndexerDefinition* const indexer, const ContextNode* const operand, const bool isLoadInstruction) : UnaryContextNode(indexer->CreationType(), operand), slotCount(-1), isLoadInstruction(isLoadInstruction), indexer(indexer)
    { }

    MemberType DefinedIndexerExpression::MemberType() const { return MemberType::DefinedIndexerExpression; }

    int DefinedIndexerExpression::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    bool DefinedIndexerExpression::Readable() const { return indexer->Readable(); }
    bool DefinedIndexerExpression::Writable() const { return indexer->Writable() && creationType->MemberType() == MemberType::Class; }

    string DefinedIndexerExpression::CILInstruction() const
    {
        if (isLoadInstruction)
            return std::format("call {}", indexer->SignatureGetString());

        return std::format("call {}", indexer->SignatureSetString());
    }
}


