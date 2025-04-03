#include "collection_construction_call_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    CollectionConstructorCallNode::CollectionConstructorCallNode(const ParseNode* const type, const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    {
        AddChild(type);
    }

    NodeType CollectionConstructorCallNode::NodeType() const { return NodeType::CollectionConstructorCall; }
}

