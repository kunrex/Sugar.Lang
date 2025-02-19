#include "initialisation_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Statements
{
    InitialisationNode::InitialisationNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier, const ParseNode* const value, const Token& separator) : DeclarationNode(describer, type, identifier, separator), value(value)
    { }

    NodeType InitialisationNode::NodeType() const { return NodeType::Initialisation; }

    const ParseNode* InitialisationNode::Value() const { return value; }

    InitialisationNode::~InitialisationNode()
    {
        delete value;
    }
}
