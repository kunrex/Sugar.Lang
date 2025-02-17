#include "keyword_type_node.h"

using namespace Tokens;

namespace ParseNodes::Types
{
    KeywordTypeNode::KeywordTypeNode(const Token& keyword) : ParseNode(), keyword(keyword)
    { }

    unsigned long KeywordTypeNode::Index() const { return keyword.Index();}
}
