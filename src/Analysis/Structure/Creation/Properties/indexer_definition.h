#ifndef INDEXER_DEFINITION_H
#define INDEXER_DEFINITION_H

#include "../../Core/created.h"
#include "../../Core/describable.h"
#include "../../Core/Creation/property_signature.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Creation
{
    class IndexerDefinition : public Global::GlobalNode, public Core::Describable, public Core::Created, public virtual Core::PropertySignature, public virtual Core::Interfaces::IIndexerDefinition
    {
        protected:
            IndexerDefinition(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };
}

#endif
