#include "describer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Describers
{
    DescriberNode::DescriberNode() : ParseNode(), tokens()
    { }

    NodeType DescriberNode::NodeType() const { return NodeType::Describer; }

    void DescriberNode::PushToken(const Token* token)
    {
        tokens.push_back(token);
    }

    int DescriberNode::TokenCount() const { return tokens.size(); }
    const Token& DescriberNode::TokenAt(const int i) const { return *tokens.at(i); }
}
