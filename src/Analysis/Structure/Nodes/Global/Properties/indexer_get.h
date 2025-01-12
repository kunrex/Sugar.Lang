#ifndef INDEXER_GET_H
#define INDEXER_GET_H

#include "../../../Core/Creation/getable.h"
#include "../../Creation/Properties/Accessors/get.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class IndexerGet final : public Creation::IndexerDefinition, public Core::Getable
    {
        public:
            IndexerGet(Enums::Describer describer, const Core::DataType* creationType, Creation::Get* get);
    };
}

#endif
