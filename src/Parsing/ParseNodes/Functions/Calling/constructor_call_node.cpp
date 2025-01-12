#include "constructor_call_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    ConstructorCallNode::ConstructorCallNode(const ParseNode* type, const Token& keyword) : NodeCollection(), type(type), keyword(keyword)
    { }

    NodeType ConstructorCallNode::NodeType() const { return NodeType::ConstructorCall; }

    const ParseNode* ConstructorCallNode::Type() const { return type; }

    const Token& ConstructorCallNode::Keyword() const { return keyword; }

    ConstructorCallNode::~ConstructorCallNode()
    {
        delete type;
    }
}
