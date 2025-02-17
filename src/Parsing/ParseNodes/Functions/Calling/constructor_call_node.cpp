#include "constructor_call_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    ConstructorCallNode::ConstructorCallNode(const ParseNode* type, const Token& keyword) : NodeCollection(), type(type), keyword(keyword)
    { }

    NodeType ConstructorCallNode::NodeType() const { return NodeType::ConstructorCall; }

    const ParseNode* ConstructorCallNode::Type() const { return type; }

    unsigned long ConstructorCallNode::Index() const { return keyword.Index(); }

    ConstructorCallNode::~ConstructorCallNode()
    {
        delete type;
    }
}
