#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "../../DataTypes/class.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Exception final : public DataTypes::ImplicitClass, public Services::SingletonService
    {
        private:
            static Exception instance;

            const Core::Interfaces::ICharacteristic* message;

            const Core::Interfaces::IConstructor* constructor;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;

            Exception();

        public:
            static const Exception* Instance();
            static void BindGlobalInstance();

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Exception() override;
    };
}

#endif
