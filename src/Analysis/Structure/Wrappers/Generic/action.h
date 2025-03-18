#ifndef ACTION_H
#define ACTION_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h""
#include "../../Core/Interfaces/DataTypes/i_delegate_type.h"

namespace Analysis::Structure::Wrappers
{
    class Action final : public DataTypes::BuiltInClass, public Services::SingletonCollection, public virtual Core::Interfaces::IDelegateType
    {
        private:
            mutable std::string genericSignature;

            std::vector<const IDataType*> types;

            Action();

        public:
            static const Action* Instance(const std::vector<const IDataType*>& types);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long TypeCount() const;
            [[nodiscard]] const IDataType* TypeAt(unsigned long index) const;

            [[nodiscard]] const std::string& DelegateSignature() const override;

            void InitializeMembers() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;
    };
}

#endif