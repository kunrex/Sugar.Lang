#ifndef BUILT_IN_INDEXER_H
#define BUILT_IN_INDEXER_H

#include <vector>

#include "../../Core/built_in_function.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInIndexer final : public Creation::IndexerDefinition, public Core::Interfaces::BuiltInFunction
    {
        protected:
            const bool readable;
            const bool writable;

        public:
            BuiltInIndexer(const Core::Interfaces::IDataType* creationType, bool readable, const std::string& getInstruction, bool writable, const std::string& setInstruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;
    };
}

#endif
