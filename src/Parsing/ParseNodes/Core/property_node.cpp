#include "property_node.h"

using namespace ParseNodes::Properties;

namespace ParseNodes::Core
{
    PropertyNode::PropertyNode(const GetNode* get, const SetNode* set) : get(get), set(set)
    { }

    const GetNode* PropertyNode::Get() const { return get; }
    const SetNode* PropertyNode::Set() const { return set; }

    PropertyNode::~PropertyNode()
    {
        delete get;
        delete set;
    }
}
