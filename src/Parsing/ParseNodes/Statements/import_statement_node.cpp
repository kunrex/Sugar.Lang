#include "import_statement_node.h"

using namespace std;

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ImportStatementNode::ImportStatementNode(const Tokens::Token& path) : ParseNode(path)
    { }

    NodeType ImportStatementNode::NodeType() const { return NodeType::Import; }

    void ImportStatementNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Import Statement Node: " << *token.Value<string>() << std::endl;
    }
}
