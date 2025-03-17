#ifndef STRING_H
#define STRING_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Global/BuiltIn/built_in_indexer.h"

namespace Analysis::Structure::Wrappers
{
    class String final : public DataTypes::BuiltInClass, public Services::SingletonService<String>
    {
        protected:
            std::map<std::string, const Core::Interfaces::ICharacteristic*> characteristics;

            std::map<unsigned long, const Core::Interfaces::IFunctionDefinition*> functions;

            Global::BuiltInIndexer* indexer;

            std::map<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*> overloads;

            String();

        public:
            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void InitializeMembers() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~String() override;
    };
}

#endif
