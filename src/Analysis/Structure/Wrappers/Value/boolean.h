#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"

namespace Analysis::Structure::Wrappers
{
    class Boolean final : public DataTypes::BuiltInValueType, public Services::SingletonService<Boolean>
    {
        protected:
            std::map<unsigned long, const Core::Interfaces::IFunction*> implicitCasts;
            std::map<unsigned long, const Core::Interfaces::IFunction*> explicitCasts;

            std::map<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*> overloads;

            Boolean();

        public:
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void InitializeMembers() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Boolean() override;
    };
}

#endif
