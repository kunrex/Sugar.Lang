#include "assigned_property_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    AssignedPropertyNode::AssignedPropertyNode(const DescriberNode* describer, const ParseNode* type, const IdentifierNode* identifier, const GetNode* get, const SetNode* set, const ParseNode* value) : BasePropertyNode(describer, type, identifier, get, set), value(value)
    { }

    NodeType AssignedPropertyNode::NodeType() const { return NodeType::PropertyInitialisation; }

    const ParseNode* AssignedPropertyNode::Value() const { return value; }

    AssignedPropertyNode::~AssignedPropertyNode()
    {
        delete value;
    }
}
