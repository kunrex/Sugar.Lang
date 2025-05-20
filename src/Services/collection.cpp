#include "collection.h"

#include "../Exceptions/compile_exception.h"

#include "../Lexing/Tokens/token.h"

#include "../Parsing/ParseNodes/parse_node.h"
#include "../Parsing/ParseNodes/Statements/declaration_node.h"

#include "../Analysis/Structure/source_object.h"
#include "../Analysis/Structure/Context/context_node.h"
#include "../Analysis/Structure/Local/Variables/local_variable.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens;

using namespace ParseNodes;
using namespace ParseNodes::Statements;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Core::Interfaces;

namespace Services
{
    template <typename TChild>
    Collection<TChild>::Collection() : children()
    { }

    template <typename TChild>
    int Collection<TChild>::ChildCount() const { return children.size(); }

    template <typename TChild>
    TChild* Collection<TChild>::GetChild(int index) const
    {
        return children.at(index);
    }

    template <typename TChild>
    void Collection<TChild>::AddChild(TChild* child)
    {
        children.push_back(child);
    }

    template <typename TChild>
    typename std::vector<TChild*>::const_iterator Collection<TChild>::begin() const
    {
        return children.begin();
    }

    template <typename TChild>
    typename std::vector<TChild*>::const_iterator Collection<TChild>::end() const
    {
        return children.end();
    }

    template <typename TChild>
    Collection<TChild>::~Collection()
    {
        if (children.size() > 0)
        {
            for (auto child: children)
                delete child;

            children.clear();
        }
    }

    template <typename TChild>
    ConstantCollection<TChild>::ConstantCollection() : Collection<const TChild>()
    { }

    template class Collection<SourceObject>;

    template class Collection<const IContextNode>;
    template class Collection<const LocalVariable>;
    template class Collection<const CompileException>;

    template class ConstantCollection<IContextNode>;
    template class ConstantCollection<LocalVariable>;
    template class ConstantCollection<CompileException>;
}