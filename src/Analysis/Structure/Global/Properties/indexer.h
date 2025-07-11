#ifndef INDEXER_H
#define INDEXER_H

#include "../../Core/created.h"
#include "../../Core/describable.h"
#include "../../Core/Interfaces/Creation/i_indexer_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"
#include "../../Core/Interfaces/Creation/i_built_in_parametrized.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class IndexerDefinition : public Core::Describable, public Core::Created, public Services::Printable, public virtual Core::Interfaces::IIndexerDefinition
    {
        protected:
            IndexerDefinition(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };

    class Indexer : public IndexerDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
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
            const Core::Interfaces::IFunction* get;
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

    class BuiltInIndexer final : public IndexerDefinition, public virtual Core::Interfaces::IBuiltInParametrized
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
