#include "throw_statement_node.h"

#include "../Enums/child_code.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ThrowStatementNode::ThrowStatementNode(const ParseNode* const exception, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Expression, exception);
    }

    NodeType ThrowStatementNode::NodeType() const { return NodeType::Throw; }
}
