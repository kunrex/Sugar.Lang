#ifndef MATH_H
#define MATH_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"

namespace Analysis::Structure::Wrappers
{
    class Math final : public DataTypes::BuiltInClass, public Services::SingletonService
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

            std::vector<std::tuple<unsigned long, const Core::Interfaces::IFunctionDefinition*>> functions;

            Math();

        public:
            static const Math* Instance();

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Math() override;
    };
}

#endif
