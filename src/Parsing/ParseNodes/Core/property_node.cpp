#include "property_node.h"

using namespace ParseNodes::Properties;

namespace ParseNodes::Core
{
    PropertyNode::PropertyNode(const GetNode* const get, const SetNode* const set) : get(get), set(set)
    { }

    const GetNode* PropertyNode::Get() const { return get; }
    const SetNode* PropertyNode::Set() const { return set; }

    PropertyNode::~PropertyNode()
    {
        delete get;
        delete set;
    }
}
