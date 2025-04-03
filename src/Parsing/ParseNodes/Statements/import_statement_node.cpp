#include "import_statement_node.h"

using namespace std;

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ImportStatementNode::ImportStatementNode(const Tokens::Token& path) : ParseNode(path)
    { }

    NodeType ImportStatementNode::NodeType() const { return NodeType::Import; }
}
