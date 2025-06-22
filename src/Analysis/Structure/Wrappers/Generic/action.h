#ifndef ACTION_H
#define ACTION_H

#include "../../DataTypes/class.h"
#include "../../Core/Interfaces/DataTypes/i_delegate_type.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Action final : public DataTypes::ImplicitClass, public Services::SingletonService, public virtual Core::Interfaces::IDelegateType
    {
        private:
            mutable std::string genericSignature;

            std::vector<const IDataType*> types;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;

            Action();

        public:
            static const Action* Instance(const std::vector<const IDataType*>& types);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long TypeCount() const override;
            [[nodiscard]] const IDataType* TypeAt(unsigned long index) const override;

            [[nodiscard]] const std::string& DelegateSignature() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Action() override;
    };
}

#endif