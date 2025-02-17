#include "statement_node.h"

namespace ParseNodes::Statements
{
    StatementNode::StatementNode(const Tokens::Token& separator) : separator(separator)
    { }

    unsigned long StatementNode::Index() const { return separator.Index(); }
}
