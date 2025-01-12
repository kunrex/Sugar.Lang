#include "dictionary_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    DictionaryTypeNode::DictionaryTypeNode(const Token& keyword, const GenericNode* generic) : GenericTypeNode(keyword, generic)
    { }

    NodeType DictionaryTypeNode::NodeType() const { return NodeType::DictionaryType; }
}