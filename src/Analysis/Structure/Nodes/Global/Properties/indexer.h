#ifndef INDEXER_H
#define INDEXER_H

#include "../../Creation/Functions/method_definition.h"
#include "../../Creation/Functions/void_definition.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Global
{
    class Indexer final : public Creation::IndexerDefinition
    {
        private:
            const Creation::MethodDefinition* get;
            const Creation::VoidDefinition* set;

            mutable bool readable;
            mutable std::string getInstruction;

            mutable bool writable;
            mutable std::string setInstruction;

        public:
            Indexer(Enums::Describer describer, const Core::DataType* creationType, const Creation::MethodDefinition* get, const Creation::VoidDefinition* set);

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
