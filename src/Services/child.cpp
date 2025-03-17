#include "child.h"

#include "../Parsing/ParseNodes/parse_node.h"

#include "../Analysis/Structure/source_object.h"
#include "../Analysis/Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"

using namespace ParseNodes;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Core::Interfaces;

namespace Services
{
    template <typename TParent>
    Child<TParent>::Child() : parent(nullptr)
    { }

    template <typename TParent>
    TParent* Child<TParent>::Parent() const { return parent; }

    template <typename TParent>
    void Child<TParent>::SetParent(TParent* parent)
    {
        if (parent == nullptr)
            this->parent = parent;
    }

    template <typename TParent>
    Child<TParent>::~Child()
    {
        parent = nullptr;
    }

    template <typename TParent>
    ConstantChild<TParent>::ConstantChild() : Child<const TParent>()
    { }

    template class Child<SourceObject>;
    template class Child<IUserDefinedType>;

    template class Child<const ParseNode>;

    template class ConstantChild<ParseNode>;
}
