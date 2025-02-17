#include "invalid_cast_node.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidCastNode::InvalidCastNode(const Core::DataType* creationType, const ContextNode* operand) : UnaryContextNode(creationType, operand)
    { }

    MemberType InvalidCastNode::MemberType() const { return MemberType::Invalid; }

    bool InvalidCastNode::Readable() const { return false; }
    bool InvalidCastNode::Writable() const { return false; }

    std::string InvalidCastNode::InstructionGet() const { return ""; }
    std::string InvalidCastNode::InstructionSet() const { return ""; }
}
