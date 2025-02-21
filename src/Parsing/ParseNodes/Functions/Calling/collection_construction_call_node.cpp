#include "collection_construction_call_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    CollectionConstructorCallNode::CollectionConstructorCallNode(const ParseNode* const type, const Groups::ScopeNode* const scope) : ParseNode(), type(type), scope(scope)
    { }

    NodeType CollectionConstructorCallNode::NodeType() const { return NodeType::CollectionConstructorCall; }

    unsigned long CollectionConstructorCallNode::Index() const { return scope->Index(); }

    CollectionConstructorCallNode::~CollectionConstructorCallNode()
    {
        delete type;
        delete scope;
    }
}

