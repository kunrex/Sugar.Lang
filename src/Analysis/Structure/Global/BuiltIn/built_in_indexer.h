#ifndef BUILT_IN_INDEXER_H
#define BUILT_IN_INDEXER_H

#include <vector>

#include "../../Creation/Properties/indexer_definition.h"
#include "../../Core/Interfaces/Creation/i_built_in_parametrized.h"

namespace Analysis::Structure::Global
{
    class BuiltInIndexer final : public Creation::IndexerDefinition, public virtual Core::Interfaces::IBuiltInParametrized
    {
        private:
            const bool readable;
            const bool writable;

            const std::string getInstruction;
            const std::string setInstruction;

            std::vector<const Core::Interfaces::IDataType*> parameters;

        public:
            BuiltInIndexer(const Core::Interfaces::IDataType* creationType, bool readable, std::string getInstruction, bool writable, std::string setInstruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            void PushParameterType(const Core::Interfaces::IDataType* type) override;
    };
}

#endif
