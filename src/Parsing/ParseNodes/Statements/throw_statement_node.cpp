#include "throw_statement_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ThrowStatementNode::ThrowStatementNode(const ParseNode* exception, const Token& keyword, const Token& separator) : StatementNode(separator), exception(exception), keyword(keyword)
    { }

    NodeType ThrowStatementNode::NodeType() const { return NodeType::Throw; }

    const ParseNode* ThrowStatementNode::Exception() const { return exception; }

    unsigned long ThrowStatementNode::Index() const { return exception->Index(); }

    ThrowStatementNode::~ThrowStatementNode()
    {
        delete exception;
    }
}
