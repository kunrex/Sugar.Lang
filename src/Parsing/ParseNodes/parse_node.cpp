#include "parse_node.h"

#include "Conditions/condition_node.h"
#include "Statements/declaration_node.h"

using namespace std;

using namespace Tokens;

using namespace Services;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Conditions;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Core::Interfaces;

namespace ParseNodes
{
    ParseNode::ParseNode(const Tokens::Token& token) : token(token)
    { }

    const Token& ParseNode::Token() const { return token; }

    int ParseNode::ChildCount() const { return 0; }
    const IParseNode* ParseNode::GetChild(const int index) const { return nullptr; }

    template <int childCount>
    FixedNodeCollection<childCount>::FixedNodeCollection(const Tokens::Token& token) : ParseNode(token), children()
    { }

    template <int childCount>
    int FixedNodeCollection<childCount>::ChildCount() const { return childCount; }

    template <int childCount>
    const IParseNode* FixedNodeCollection<childCount>::GetChild(const int index) const
    {
        for (const auto child: children)
            if (std::get<0>(child) == index)
                return std::get<1>(child);

        return nullptr;
    }

    template <int childCount>
    void FixedNodeCollection<childCount>::AddChild(const ChildCode code, const IParseNode* const child)
    {
        for (auto i = 0; i < childCount; i++)
            if (std::get<1>(children.at(i)) == nullptr)
            {
                children[0] = std::tuple(code, child);
                break;
            }
    }

    DynamicNodeCollection::DynamicNodeCollection(const Tokens::Token& token) : ParseNode(token), children()
    { }

    int DynamicNodeCollection::ChildCount() const { return static_cast<int>(children.size()); }

    const IParseNode* DynamicNodeCollection::GetChild(const int index) const
    {
        return children.at(index);
    }

    void DynamicNodeCollection::AddChild(const IParseNode* const child)
    {
        children.push_back(child);
    }
}
