#ifndef DICTIONARY_WRAPPER_H
#define DICTIONARY_WRAPPER_H

#include <array>

#include "../../DataTypes/class.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Dictionary final : public DataTypes::BuiltInClass, public Services::SingletonService
    {
        private:
            mutable std::string genericSignature;

            const IDataType* keyType;
            const IDataType* valueType;

            const Core::Interfaces::ICharacteristic* count;

            std::array<std::pair<unsigned long, const Core::Interfaces::IFunctionDefinition*>, 5> functions;

            const Core::Interfaces::IConstructor* constructor;

            const Core::Interfaces::IIndexerDefinition* indexer;

            const Core::Interfaces::IFunction* implicitObject;

            const Core::Interfaces::IFunction* explicitString;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;

            explicit Dictionary(const IDataType* keyType, const IDataType* valueType);

        public:
            static const Dictionary* Instance(const IDataType* keyType, const IDataType* valueType);

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

            ~Dictionary() override;
    };
}

#endif
