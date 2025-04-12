#include "describer_keyword_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Describers
{
    DescriberKeywordNode::DescriberKeywordNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType DescriberKeywordNode::NodeType() const { return NodeType::Describer; }

    void DescriberKeywordNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Describer Keyword Node: " << ToString(token.Kind()) << std::endl;
    }
}
