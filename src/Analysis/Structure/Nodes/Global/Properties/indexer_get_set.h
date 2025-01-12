#ifndef INDEXER_GET_SET_H
#define INDEXER_GET_SET_H

#include "../../../Core/Creation/get_set.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class IndexerGetSet final : public Creation::IndexerDefinition, public Core::GetSet
    {
        public:
            IndexerGetSet(Enums::Describer describer, const Core::DataType* creationType, Creation::Get* get, Creation::Set* set);
    };
}

#endif
