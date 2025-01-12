#include "operator_overload_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    OperatorOverloadNode::OperatorOverloadNode(const DescriberNode* describer, const ParseNode* type, const Token& base, const CompoundDeclarationNode* parameters, const ParseNode* body, const Token& keyword) : KeywordFunctionNode(describer, type, parameters, body, keyword), base(base)
    { }

    NodeType OperatorOverloadNode::NodeType() const { return NodeType::OperatorOverload; }

    const Token& OperatorOverloadNode::Operator() const { return base; }
}

