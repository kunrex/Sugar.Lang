#include "assigned_property_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    AssignedPropertyNode::AssignedPropertyNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier, const GetNode* const get, const SetNode* const set, const ParseNode* const value) : BasePropertyNode(describer, type, identifier, get, set), value(value)
    { }

    NodeType AssignedPropertyNode::NodeType() const { return NodeType::PropertyInitialisation; }

    const ParseNode* AssignedPropertyNode::Value() const { return value; }

    AssignedPropertyNode::~AssignedPropertyNode()
    {
        delete value;
    }
}
