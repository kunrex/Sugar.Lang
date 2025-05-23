#ifndef INDEXER_H
#define INDEXER_H

#include "../../Creation/Functions/void_definition.h"
#include "../../Creation/Functions/method_definition.h"
#include "../../Creation/Properties/indexer_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class Indexer final : public Creation::IndexerDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            const Creation::MethodDefinition* get;
            const Creation::VoidDefinition* set;

            mutable bool readable;
            mutable std::string getInstruction;

            mutable bool writable;
            mutable std::string setInstruction;

        public:
            Indexer(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Creation::MethodDefinition* get, const Creation::VoidDefinition* set);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
