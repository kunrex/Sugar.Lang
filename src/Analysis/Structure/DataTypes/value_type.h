#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H

#include <map>

#include "../Core/DataTypes/data_type.h"
#include "../Core/Interfaces/DataTypes/i_user_defined_type.h"
#include "../Global/Functions/constructor.h"

namespace Analysis::Structure::DataTypes
{
    class ValueType : public Core::DataType
    {
        protected:
            mutable int slotCount;

            std::map<std::string, Core::Interfaces::ICharacteristic*> characteristics;

        public:
            ValueType(const std::string& name, Enums::Describer describer);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            ~ValueType() override;
    };

    class BuiltInValueType : public ValueType
    {
        protected:
            BuiltInValueType(const std::string& name, Enums::Describer describer);

            virtual void InitializeMembers() = 0;

        public:
            [[nodiscard]] const std::string& FullName() const override;
    };

    class StructSource final : public ValueType, public virtual Core::Interfaces::IUserDefinedType
    {
        private:
            const ParseNodes::DataTypes::DataTypeNode* skeleton;

            mutable std::string fullName;

            std::map<unsigned long, Core::Interfaces::IFunctionDefinition*> functions;

            Global::StaticConstructor* const staticConstructor;
            Global::InstanceConstructor* const instanceConstructor;
            std::map<unsigned long, Core::Interfaces::IFunction*> constructors;

            std::map<unsigned long, Core::Interfaces::IIndexerDefinition*> indexers;

            std::map<unsigned long, Core::Interfaces::IFunction*> implicitCasts;
            std::map<unsigned long, Core::Interfaces::IFunction*> explicitCasts;

            std::map<Tokens::Enums::SyntaxKind, Core::Interfaces::IOperatorOverload*> overloads;

        public:
            StructSource(const std::string& name, Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const ParseNodes::DataTypes::DataTypeNode* Skeleton() const override;

            void PushCharacteristic(Core::Interfaces::ICharacteristic* characteristic) override;

            void PushFunction(Core::Interfaces::IFunctionDefinition* function) override;
            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] Core::Interfaces::IScoped* StaticConstructor() const override;
            [[nodiscard]] Core::Interfaces::IScoped* InstanceConstructor() const override;

            void PushConstructor(Core::Interfaces::IFunction* constructor) override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            void PushIndexer(Core::Interfaces::IIndexerDefinition* indexer) override;
            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            void PushImplicitCast(Core::Interfaces::IFunction* cast) override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            void PushExplicitCast(Core::Interfaces::IFunction* cast) override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            void PushOverload(Core::Interfaces::IOperatorOverload* overload) override;
            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            [[nodiscard]] std::vector<const Core::Interfaces::ICharacteristic*> AllCharacteristics() const override;
            [[nodiscard]] std::vector<Core::Interfaces::IScoped*> AllScoped() const override;

            ~StructSource() override;
    };
}


#endif
