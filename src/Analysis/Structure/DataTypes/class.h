#ifndef CLASS_H
#define CLASS_H

#include <map>

#include "../Core/DataTypes/data_type.h"
#include "../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../Global/Functions/constructor.h"

namespace Analysis::Structure::DataTypes
{
    class Class : public Core::DataType
    {
        public:
            Class(const std::string& name, Enums::Describer describer);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;
    };

    class BuiltInClass : public Class
    {
        protected:
            BuiltInClass(const std::string& name, Enums::Describer describer);

            virtual void InitializeMembers() = 0;

        public:
            [[nodiscard]] const std::string& FullName() const override;
    };

    class ClassSource final : public Class, public virtual Core::Interfaces::IUserDefinedType
    {
        private:
            const ParseNodes::Core::Interfaces::IParseNode* skeleton;

            mutable std::string fullName;

            std::map<std::string, Core::Interfaces::ICharacteristic*> characteristics;

            std::map<unsigned long, Core::Interfaces::IFunctionDefinition*> functions;

            std::map<unsigned long, Core::Interfaces::IFunction*> constructors;

            std::map<unsigned long, Core::Interfaces::IIndexerDefinition*> indexers;

            std::map<unsigned long, Core::Interfaces::IFunction*> implicitCasts;
            std::map<unsigned long, Core::Interfaces::IFunction*> explicitCasts;

            std::map<Tokens::Enums::SyntaxKind, Core::Interfaces::IOperatorOverload*> overloads;

        public:
            ClassSource(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* skeleton);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* Skeleton() const override;

            [[nodiscard]] unsigned long ConstructorCount() const override;

            void PushCharacteristic(Core::Interfaces::ICharacteristic* characteristic) override;
            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            void PushFunction(Core::Interfaces::IFunctionDefinition* function) override;
            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

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

            [[nodiscard]] std::vector<Core::Interfaces::ICharacteristic*> AllCharacteristics() const override;
            [[nodiscard]] std::vector<Core::Interfaces::IScoped*> AllScoped() const override;

            void Print(const std::string& indent, bool last) const override;

            ~ClassSource() override;
    };
}

#endif
