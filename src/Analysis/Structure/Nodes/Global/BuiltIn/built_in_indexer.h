#ifndef BUILT_IN_INDEXER_H
#define BUILT_IN_INDEXER_H

#include <vector>

#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInIndexer final : public Creation::IndexerDefinition
    {
        protected:
            const bool readable;
            const bool writable;

            std::vector<const Core::DataType*> parameterTypes;

        public:
            BuiltInIndexer(const Core::DataType* creationType, bool readable, const std::string& getInstruction, bool writable, const std::string& setInstruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            [[nodiscard]] int ParameterCount() const override;
            [[nodiscard]] const Core::DataType* ParameterAt(int index) const override;
    };
}

#endif
