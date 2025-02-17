#include "describer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Describers
{
    DescriberNode::DescriberNode(const unsigned long index) : ParseNode(), index(index), tokens()
    { }

    NodeType DescriberNode::NodeType() const { return NodeType::Describer; }

    void DescriberNode::PushToken(const Token* token)
    {
        tokens.push_back(token);
    }

    unsigned long DescriberNode::TokenCount() const { return tokens.size(); }
    const Token& DescriberNode::TokenAt(const int i) const { return *tokens.at(i); }

    unsigned long DescriberNode::Index() const { return index; }
}
