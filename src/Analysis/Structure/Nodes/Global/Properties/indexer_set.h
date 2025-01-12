#ifndef INDEXER_SET_H
#define INDEXER_SET_H

#include "../../../Core/Creation/setable.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class IndexerSet final : public Creation::IndexerDefinition, public Core::Setable
    {
        public:
            IndexerSet(Enums::Describer describer, const Core::DataType* creationType, Creation::Set* get);
    };
}

#endif
