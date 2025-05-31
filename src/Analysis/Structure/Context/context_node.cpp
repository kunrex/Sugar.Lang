#include "context_node.h"

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ContextNode::ContextNode(const IDataType* const creationType) : Created(creationType)
    { }

    uintptr_t ContextNode::Metadata() const { return 0; }

    unsigned long ContextNode::ChildCount() const { return 0; }
    const IContextNode* ContextNode::GetChild(const int index) const { return nullptr; }

    template <int childCount>
    FixedContextCollection<childCount>::FixedContextCollection(const IDataType* const creationType) : Created(creationType), children()
    { }

    template <int childCount>
    unsigned long FixedContextCollection<childCount>::ChildCount() const { return childCount; }

    template <int childCount>
    const IContextNode* FixedContextCollection<childCount>::GetChild(int index) const
    {
        for (const auto child: children)
            if (std::get<0>(child) == index)
                return std::get<1>(child);

        return nullptr;
    }

    template <int childCount>
    uintptr_t FixedContextCollection<childCount>::Metadata() const { return 0; }

    template <int childCount>
    void FixedContextCollection<childCount>::AddChild(const ChildCode code, const IContextNode* const context)
    {
        for (auto i = 0; i < childCount; i++)
            if (std::get<1>(children.at(i)) == nullptr)
            {
                children[i] = std::tuple(static_cast<int>(code), context);
                break;
            }
    }

    template <int childCount>
    FixedContextCollection<childCount>::~FixedContextCollection()
    {
        for (const auto child: children)
            delete std::get<1>(child);
    }

    template <int childCount>
    void FixedContextCollection<childCount>::Print(const std::string& indent, const bool last) const
    {
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        for (const auto child: children)
            std::get<1>(child)->Print(next, ++i == children.size());
    }

    DynamicContextCollection::DynamicContextCollection(const IDataType* const creationType) : Created(creationType), children()
    { }

    uintptr_t DynamicContextCollection::Metadata() const { return 0; }

    unsigned long DynamicContextCollection::ChildCount() const { return children.size(); }
    const IContextNode* DynamicContextCollection::GetChild(const int index) const { return children.at(index); }

    void DynamicContextCollection::AddChild(const IContextNode* const child)
    {
        children.push_back(child);
    }

    DynamicContextCollection::~DynamicContextCollection()
    {
        for (const auto child: children)
            delete child;
    }

    void DynamicContextCollection::Print(const std::string& indent, bool last) const
    {
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        for (const auto child: children)
            child->Print(next, ++i == children.size());
    }

    template class FixedContextCollection<1>;
    template class FixedContextCollection<2>;
    template class FixedContextCollection<3>;
}