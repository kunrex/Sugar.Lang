#include "generic_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    GenericTypeNode::GenericTypeNode(const Token& keyword, const Groups::GenericNode* generic) : KeywordTypeNode(keyword), generic(generic)
    { }

    const GenericNode* GenericTypeNode::Generic() const { return generic; }

    GenericTypeNode::~GenericTypeNode()
    {
        delete generic;
    }
}