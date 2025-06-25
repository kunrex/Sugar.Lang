#include "parse_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

namespace ParseNodes
{
    ParseNode::ParseNode(const Tokens::Token& token) : token(token)
    { }

    const Token& ParseNode::Token() const { return token; }

    unsigned long ParseNode::ChildCount() const { return 0; }
    const IParseNode* ParseNode::GetChild(const int index) const { return nullptr; }

    template <int childCount>
    FixedNodeCollection<childCount>::FixedNodeCollection(const Tokens::Token& token) : ParseNode(token), children()
    { }

    template <int childCount>
    unsigned long FixedNodeCollection<childCount>::ChildCount() const { return childCount; }

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
                children[i] = std::tuple(static_cast<int>(code), child);
                break;
            }
    }

    template <int childCount>
    FixedNodeCollection<childCount>::~FixedNodeCollection()
    {
        for (const auto child: children)
            delete std::get<1>(child);
    }

    DynamicNodeCollection::DynamicNodeCollection(const Tokens::Token& token) : ParseNode(token), children()
    { }

    unsigned long DynamicNodeCollection::ChildCount() const { return children.size(); }

    const IParseNode* DynamicNodeCollection::GetChild(const int index) const
    {
        return children[index];
    }

    void DynamicNodeCollection::AddChild(const IParseNode* const child)
    {
        children.push_back(child);
    }

    DynamicNodeCollection::~DynamicNodeCollection()
    {
        for (const auto child: children)
            delete child;
    }

    template class FixedNodeCollection<1>;
    template class FixedNodeCollection<2>;
    template class FixedNodeCollection<3>;
    template class FixedNodeCollection<4>;
    template class FixedNodeCollection<5>;
    template class FixedNodeCollection<6>;
}
