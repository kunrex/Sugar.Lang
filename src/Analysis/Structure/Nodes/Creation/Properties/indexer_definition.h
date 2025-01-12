#ifndef INDEXER_DEFINITION_H
#define INDEXER_DEFINITION_H

#include "../../../Core/Creation/function.h"

constexpr std::string_view get_indexer = "__index_get__Item";
constexpr std::string_view set_indexer = "__index_set__Item";

namespace Analysis::Structure::Creation
{
    class IndexerDefinition : public Core::Function
    {
        protected:
            IndexerDefinition(Enums::Describer describer, const Core::DataType* creationType);

        public:
            [[nodiscard]] std::string SignatureStringSet() const;
    };
}

#endif
