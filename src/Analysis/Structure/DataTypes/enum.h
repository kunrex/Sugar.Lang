#ifndef ENUM_H
#define ENUM_H

#include <tuple>
#include <vector>

#include "../Core/DataTypes/data_type.h"
#include "../Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class Enum final : public Core::DataType, public virtual Core::Interfaces::IUserDefinedType
    {
        protected:
            const ParseNodes::Core::Interfaces::IParseNode* skeleton;

            mutable std::string fullName;

            std::vector<Core::Interfaces::ICharacteristic*> characteristics;

            std::vector<std::tuple<unsigned long, Core::Interfaces::IFunction*>> explicitCasts;

            std::vector<std::tuple<Tokens::Enums::SyntaxKind, Core::Interfaces::IOperatorOverload*>> overloads;

        public:
            Enum(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* skeleton);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* LastCharacteristic() const;

            void PushCharacteristic(Core::Interfaces::ICharacteristic* characteristic) override;
            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            void PushFunction(Core::Interfaces::IFunctionDefinition* function) override;
            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            void PushConstructor(Core::Interfaces::IConstructor* constructor) override;
            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] Core::Interfaces::IConstructor* StaticConstructor() const override;
            [[nodiscard]] Core::Interfaces::IConstructor* InstanceConstructor() const override;

            void PushIndexer(Core::Interfaces::IIndexerDefinition* indexer) override;
            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            void PushImplicitCast(Core::Interfaces::IFunction* cast) override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            void PushExplicitCast(Core::Interfaces::IFunction* cast) override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            void PushOverload(Core::Interfaces::IOperatorOverload* overload) override;
            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            void BindGlobal() override;
            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void Print(const std::string& indent, bool last) const override;

            ~Enum() override;
    };
}

#endif
