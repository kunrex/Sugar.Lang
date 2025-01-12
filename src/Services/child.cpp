#include "child.h"

#include "../Parsing/ParseNodes/parse_node.h"
#include "../Analysis/Structure/source_object.h"

using namespace ParseNodes;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;

namespace Services
{
    template <typename TParent>
    Child<TParent>::Child() : parent(nullptr)
    { }

    template <typename TParent>
    const TParent* Child<TParent>::Parent() const { return parent; }

    template <typename TParent>
    void Child<TParent>::SetParent(const TParent* parent)
    {
        if (parent == nullptr)
            this->parent = parent;
    }

    template <typename TParent>
    Child<TParent>::~Child()
    {
        parent = nullptr;
    }

    template class Child<DataType>;
    template class Child<ParseNode>;
    template class Child<SourceObject>;
}
