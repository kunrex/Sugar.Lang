#include "operator_overload_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    OperatorOverloadNode::OperatorOverloadNode(const DescriberNode* const describer, const ParseNode* const type, const Token& base, const CompoundDeclarationNode* const parameters, const ScopeNode* const body, const Token& keyword) : KeywordFunctionNode(describer, type, parameters, body, keyword), base(base)
    { }

    NodeType OperatorOverloadNode::NodeType() const { return NodeType::OperatorOverload; }

    const Token& OperatorOverloadNode::Operator() const { return base; }
}

