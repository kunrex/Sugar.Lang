#include "keyword_type_node.h"

namespace ParseNodes::Types
{
    KeywordTypeNode::KeywordTypeNode(const Tokens::Token& keyword) : ParseNode(), keyword(keyword)
    { }

    const Tokens::Token& KeywordTypeNode::Keyword() const { return keyword;}
}
