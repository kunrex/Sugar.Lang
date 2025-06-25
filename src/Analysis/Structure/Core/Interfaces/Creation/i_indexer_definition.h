#ifndef I_INDEXER_DEFINITION_H
#define I_INDEXER_DEFINITION_H

#include "i_parametrized.h"
#include "i_property_signature.h"

#include "../i_node.h"
#include "../i_created.h"
#include "../i_describable.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IIndexerDefinition : public virtual INode, public virtual IDescribable, public virtual ICreated, public virtual IParametrized, public virtual IPropertySignature
    {

    };
}

#endif
