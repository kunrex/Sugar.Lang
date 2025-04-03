#include "dictionary_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    DictionaryTypeNode::DictionaryTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType DictionaryTypeNode::NodeType() const { return NodeType::DictionaryType; }
}