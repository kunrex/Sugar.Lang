#ifndef BUILT_IN_INDEXER_H
#define BUILT_IN_INDEXER_H

#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInIndexer final : public Creation::IndexerDefinition
    {
        protected:
            const std::string getInstruction;
            const std::string setInstruction;

        public:
            BuiltInIndexer(const Core::DataType* creationType, std::string getInstruction, std::string setInstruction);

            [[nodiscard]] std::string GetInstruction() const;
            [[nodiscard]] std::string SetInstruction() const;
    };
}

#endif
