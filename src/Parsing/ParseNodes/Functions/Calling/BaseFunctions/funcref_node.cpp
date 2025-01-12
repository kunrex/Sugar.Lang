#include "funcref_node.h"

#include "../../../Groups/generic_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Functions::Calling
{
    FuncRefNode::FuncRefNode(const GenericNode* generic, const Token& keyword) : BaseFunctionCallNode(keyword), generic(generic)
    { }

    NodeType FuncRefNode::NodeType() const { return NodeType::FuncRef; }

    const GenericNode* FuncRefNode::Generic() const { return generic; }

    FuncRefNode::~FuncRefNode()
    {
        delete generic;
    }
}