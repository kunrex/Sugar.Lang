#include "assignment_expression.h"

#include <iostream>

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    AssignmentExpression::AssignmentExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(lhs->CreationType(), lhs, rhs), slotCount(std::max(lhs->SlotCount(), rhs->SlotCount()))
    { }

    MemberType AssignmentExpression::MemberType() const { return MemberType::AssignmentExpression; }

    int AssignmentExpression::SlotCount() const { return slotCount; }

    bool AssignmentExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Readable(); }
    bool AssignmentExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Writable(); }

    std::string AssignmentExpression::CILData() const { return ""; }

    void AssignmentExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Assignment Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }

    AggregateAssignmentExpression::AggregateAssignmentExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(lhs->CreationType(), lhs, rhs), slotCount(std::max(lhs->SlotCount(), rhs->SlotCount()))
    { }

    MemberType AggregateAssignmentExpression::MemberType() const { return MemberType::AssignmentExpression; }

    int AggregateAssignmentExpression::SlotCount() const { return slotCount; }

    bool AggregateAssignmentExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Readable(); }
    bool AggregateAssignmentExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Writable(); }

    std::string AggregateAssignmentExpression::CILData() const { return ""; }

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

    GeneratedAssignmentExpression::GeneratedAssignmentExpression(const IContextNode* const assignment, const IContextNode* const load) : BinaryContextNode(load->CreationType(), assignment, load), slotCount(std::max(assignment->SlotCount(), load->SlotCount()))
    { }

    MemberType GeneratedAssignmentExpression::MemberType() const { return MemberType::GeneratedAssignmentExpression; }

    int GeneratedAssignmentExpression::SlotCount() const { return slotCount; }

    bool GeneratedAssignmentExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::RHS))->Readable(); }
    bool GeneratedAssignmentExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::RHS))->Writable(); }

    std::string GeneratedAssignmentExpression::CILData() const { return ""; }

    void GeneratedAssignmentExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Generated Assignment Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }

    GeneratedAssignmentExpression::~GeneratedAssignmentExpression()
    {
        for (auto& child : children)
            if (std::get<0>(child) == static_cast<int>(ChildCode::RHS))
            {
                std::get<1>(child) = nullptr;
                break;
            }
    }
}
