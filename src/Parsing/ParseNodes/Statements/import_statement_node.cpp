#include "import_statement_node.h"

using namespace std;

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ImportStatementNode::ImportStatementNode(const Token& path, const Token& keyword, const Token& separator) : StatementNode(separator), path(path), keyword(keyword)
    { }

    NodeType ImportStatementNode::NodeType() const { return NodeType::Import; }

    string ImportStatementNode::Path() const { return string(*path.Value<std::string_view>()); }
}
