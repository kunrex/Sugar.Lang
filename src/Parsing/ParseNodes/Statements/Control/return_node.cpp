#include "return_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ReturnNode::ReturnNode(const Token& separator) : StatementNode(separator), value(nullptr)
    { }

    ReturnNode::ReturnNode(const ParseNode* value, const Token& separator) : StatementNode(separator), value(value)
    { }

    NodeType ReturnNode::NodeType() const { return NodeType::Return; }

    const ParseNode* ReturnNode::Value() const { return value;}

    ReturnNode::~ReturnNode()
    {
        delete value;
    }
}
