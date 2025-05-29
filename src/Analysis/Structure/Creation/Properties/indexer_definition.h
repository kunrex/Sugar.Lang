#ifndef INDEXER_DEFINITION_H
#define INDEXER_DEFINITION_H

#include "../../Core/created.h"
#include "../../Core/describable.h"

#include "../../Core/Interfaces/Creation/i_indexer_definition.h"

namespace Analysis::Structure::Creation
{
    class IndexerDefinition : public Core::Describable, public Core::Created, public Services::Printable, public virtual Core::Interfaces::IIndexerDefinition
    {
        protected:
            IndexerDefinition(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };
}

#endif
