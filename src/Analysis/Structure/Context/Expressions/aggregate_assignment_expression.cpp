#include "aggregate_assignment_expression.h"

#include <iostream>

using namespace std;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    AggregateAssignmentExpression::AggregateAssignmentExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(lhs->CreationType(), lhs, rhs), slotCount(std::max(lhs->SlotCount(), rhs->SlotCount()))
    { }

    MemberType AggregateAssignmentExpression::MemberType() const { return MemberType::AssignmentExpression; }

    int AggregateAssignmentExpression::SlotCount() const { return slotCount; }

    bool AggregateAssignmentExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Readable(); }
    bool AggregateAssignmentExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Writable(); }

    string AggregateAssignmentExpression::CILData() const { return ""; }

    void AggregateAssignmentExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Assignment Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }

    AggregateAssignmentExpression::~AggregateAssignmentExpression()
    {
        for (auto& child : children)
            if (std::get<0>(child) == static_cast<int>(ChildCode::LHS))
            {
                std::get<1>(child) = nullptr;
                break;
            }
    }
}