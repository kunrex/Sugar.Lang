#include "child.h"

#include "../Parsing/ParseNodes/parse_node.h"

#include "../Analysis/Structure/source_object.h"
#include "../Analysis/Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
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

    template class Child<IDataType>;
    template class Child<SourceFile>;
    template class Child<SourceObject>;

    template class Child<const Scope>;
    template class Child<const IDataType>;
    template class Child<const IParseNode>;

    template class ConstantChild<Scope>;
    template class ConstantChild<IDataType>;
    template class ConstantChild<IParseNode>;
}
