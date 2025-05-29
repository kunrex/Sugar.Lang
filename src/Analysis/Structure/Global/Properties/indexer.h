#ifndef INDEXER_H
#define INDEXER_H

#include "../../Creation/Functions/void_definition.h"
#include "../../Creation/Functions/method_definition.h"
#include "../../Creation/Properties/indexer_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class Indexer : public Creation::IndexerDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        protected:
            const unsigned long parameterCount;

        public:
            Indexer(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, unsigned long parameterCount);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
    };

    class GetIndexer final : public Indexer
    {
        private:
            const std::string getInstruction;
            const Core::Interfaces::IFunction* get;

        public:
            GetIndexer(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* get);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;
    };

    class SetIndexer final : public Indexer
    {
        private:
            const std::string setInstruction;
            const Core::Interfaces::IFunction* set;

        public:
            SetIndexer(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* set);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;
    };

    class GetSetIndexer final : public Indexer
    {
        private:
            const std::string getInstruction;
            const Core::Interfaces::IFunction* get;

            const std::string setInstruction;
            const Core::Interfaces::IFunction* set;

        public:
            GetSetIndexer(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* get, const Core::Interfaces::IFunction* set);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
