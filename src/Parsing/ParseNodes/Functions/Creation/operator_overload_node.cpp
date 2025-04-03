#include "operator_overload_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    OperatorOverloadNode::OperatorOverloadNode(const DescriberNode* const describer, const ParseNode* const type, const Tokens::Token& base, const CompoundDeclarationNode* const parameters, const DynamicNodeCollection* const body) : FixedNodeCollection(base),  FunctionNode(describer, type, parameters, body)
    { }

    NodeType OperatorOverloadNode::NodeType() const { return NodeType::OperatorOverload; }
}

