#ifndef INDEXER_DEFINITION_H
#define INDEXER_DEFINITION_H

#include "../../Core/created.h"
#include "../../Core/describable.h"
#include "../../Core/property_signature.h"
#include "../../Core/Interfaces/i_parametrized.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Creation
{
    class IndexerDefinition : public Global::GlobalNode, public Core::Describable, public Core::Created, public virtual Core::PropertySignature, public virtual Core::Interfaces::IParametrized
    {
        protected:
            IndexerDefinition(Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
