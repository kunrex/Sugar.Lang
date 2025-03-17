#ifndef DICTIONARY_WRAPPER_H
#define DICTIONARY_WRAPPER_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Global/BuiltIn/built_in_constructor.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"

namespace Analysis::Structure::Wrappers
{
    class Dictionary final : public DataTypes::BuiltInClass, public Services::SingletonCollection,
    {
        private:
            mutable std::string genericSignature;

            const IDataType* keyType;
            const IDataType* valueType;

            Global::BuiltInProperty* count;

            std::map<unsigned long, const Core::Interfaces::IFunctionDefinition*> functions;

            Global::BuiltInConstructor* constructor;

            Global::BuiltInIndexer* indexer;

            explicit Dictionary(const IDataType* keyType, const IDataType* valueType);

        public:
            static const Dictionary* Instance(const IDataType* keyType, const IDataType* valueType);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void InitializeMembers() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Dictionary() override;
    };
}

#endif
