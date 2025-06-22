#ifndef CLASS_H
#define CLASS_H

#include <vector>

#include "../Core/DataTypes/data_type.h"
#include "../Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class Class : public Core::DataType
    {
        protected:
            [[nodiscard]] static Core::Interfaces::IFunctionDefinition* GetHash();

            [[nodiscard]] Core::Interfaces::IFunction* ImplicitObject() const;

        public:
            Class(const std::string& name, Enums::Describer describer);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;
    };

    class BuiltInClass : public Class
    {
        protected:
            BuiltInClass(const std::string& name, Enums::Describer describer);

        public:
            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;
    };

    class ImplicitClass : public BuiltInClass
    {
        protected:
            const Core::Interfaces::IFunctionDefinition* getHash;

            const Core::Interfaces::IFunction* explicitString;

            const Core::Interfaces::IFunction* implicitObject;

            ImplicitClass(const std::string& name, Enums::Describer describer);

            void BindGlobal() override;

        public:
            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            ~ImplicitClass() override;
    };

    class ClassSource final : public Class, public virtual Core::Interfaces::IUserDefinedType
    {
        private:
            const ParseNodes::Core::Interfaces::IParseNode* skeleton;

            mutable std::string fullName;

            std::vector<Core::Interfaces::ICharacteristic*> characteristics;

            std::vector<std::pair<unsigned long, Core::Interfaces::IFunctionDefinition*>> functions;

            std::vector<std::pair<unsigned long, Core::Interfaces::IConstructor*>> constructors;

            std::vector<std::pair<unsigned long, Core::Interfaces::IIndexerDefinition*>> indexers;

            std::vector<std::pair<unsigned long, Core::Interfaces::IFunction*>> implicitCasts;
            std::vector<std::pair<unsigned long, Core::Interfaces::IFunction*>> explicitCasts;

            std::vector<std::pair<Tokens::Enums::SyntaxKind, Core::Interfaces::IOperatorOverload*>> overloads;

        public:
            ClassSource(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* skeleton);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

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

            ~ClassSource() override;
    };
}

#endif
