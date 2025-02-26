#ifndef I_INDEXER_DEFINITION_H
#define I_INDEXER_DEFINITION_H

#include "../i_created.h"
#include "../i_describable.h"

#include "i_parametrized.h"
#include "i_property_signature.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IIndexerDefinition : public virtual IDescribable, public virtual ICreated, public virtual IParametrized, public virtual IPropertySignature
    {

    };
}

#endif
