#ifndef NULLABLE_H
#define NULLABLE_H

#include <array>

#include "../../DataTypes/value_type.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Nullable final : public DataTypes::ImplicitValueType, public Services::SingletonService
    {
        private:
            mutable std::string genericSignature;

            const IDataType* nullableType;

            std::array<const Core::Interfaces::ICharacteristic*, 2> characteristics;

            std::array<std::pair<unsigned long, const Core::Interfaces::IConstructor*>, 2> constructors;

            explicit Nullable(const IDataType* nullableType);

        public:
            static const Nullable* Instance(const IDataType* dataType);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Nullable() override;
    };
}

#endif
