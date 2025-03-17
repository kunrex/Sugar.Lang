#include "collection_construction_call_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    CollectionConstructorCallNode::CollectionConstructorCallNode(const ParseNode* const type) : ParseNode(), type(type)
    { }

    NodeType CollectionConstructorCallNode::NodeType() const { return NodeType::CollectionConstructorCall; }

    unsigned long CollectionConstructorCallNode::Index() const { return type->Index(); }

    const ParseNode* CollectionConstructorCallNode::Type() const { return type; }

    CollectionConstructorCallNode::~CollectionConstructorCallNode()
    {
        delete type;
    }
}

