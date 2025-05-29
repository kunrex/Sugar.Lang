#ifndef NULLABLE_H
#define NULLABLE_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"

namespace Analysis::Structure::Wrappers
{
    class Nullable final : public DataTypes::BuiltInValueType, public Services::SingletonService
    {
        private:
            mutable std::string genericSignature;

            const IDataType* nullableType;

            std::vector<std::tuple<unsigned long, const Core::Interfaces::IConstructor*>> constructors;

            explicit Nullable(const IDataType* nullableType);

        public:
            static const Nullable* Instance(const IDataType* dataType);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Nullable() override;
    };
}

#endif
