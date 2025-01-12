#include "statement_node.h"

namespace ParseNodes::Statements
{
    StatementNode::StatementNode(const Tokens::Token& separator) : separator(separator)
    { }

    const Tokens::Token& StatementNode::Separator() const { return separator; }
}
