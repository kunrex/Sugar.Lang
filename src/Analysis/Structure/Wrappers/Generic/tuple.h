#ifndef TUPLE_H
#define TUPLE_H

#include <map>
#include <vector>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

namespace Analysis::Structure::Wrappers
{
    class Tuple final : public DataTypes::BuiltInValueType, public Services::SingletonService
    {
        private:
            mutable std::string genericSignature;

            std::vector<const IDataType*> types;

            Global::BuiltInConstructor* constructor;

            explicit Tuple();

        public:
            static const Tuple* Instance(const std::vector<const IDataType*>& types);

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

            ~Tuple() override;
    };
}

#endif
