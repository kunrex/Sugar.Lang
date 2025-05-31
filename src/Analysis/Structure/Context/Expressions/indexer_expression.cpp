#include "indexer_expression.h"

#include <format>

#include "../Entities/Functions/function_extensions.h"

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    IndexerExpression::IndexerExpression(const IIndexerDefinition* const indexer, const IContextNode* const operand, const bool isPublic) : DynamicContextCollection(indexer->CreationType()), isPublic(isPublic), slotCount(-1), indexer(indexer)
    {
        AddChild(operand);
    }

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

    bool IndexerExpression::Readable() const { return indexer->Readable() && !isPublic || indexer->PublicGet();; }
    bool IndexerExpression::Writable() const { return indexer->Writable() && creationType->MemberType() == MemberType::Class && !isPublic || indexer->PublicSet(); }

    string IndexerExpression::CILData() const { return ""; }

    uintptr_t IndexerExpression::Metadata() const { return reinterpret_cast<uintptr_t>(indexer); }

    void IndexerExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Indexer Expression: " << GetChild(0)->CreationType()->FullName() << std::endl;
        DynamicContextCollection::Print(indent, last);
    }
}


