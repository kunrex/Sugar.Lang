#ifndef CLASS_H
#define CLASS_H

#include <map>

#include "../Core/DataTypes/data_type.h"
#include "../Core/DataTypes/user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class Class : public Core::DataType
    {
        protected:
            mutable std::string fullName;

            std::map<std::string, Core::Interfaces::ICharacteristic*> characteristics;

            std::map<unsigned long, Core::Interfaces::IFunctionDefinition*> functions;

            std::map<unsigned long, Core::Interfaces::IFunction*> constructors;

            std::map<unsigned long, Core::Interfaces::IIndexerDefinition*> indexers;

            std::map<unsigned long, Core::Interfaces::IFunction*> implicitCasts;
            std::map<unsigned long, Core::Interfaces::IFunction*> explicitCasts;

            std::map<Tokens::Enums::SyntaxKind, Core::Interfaces::IOperatorOverload*> overloads;

        public:
            Class(const std::string& name, Enums::Describer describer);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void PushCharacteristic(Core::Interfaces::ICharacteristic* characteristic) override;
            const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            void PushFunction(Core::Interfaces::IFunctionDefinition* function) override;
            const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            void PushConstructor(Core::Interfaces::IFunction* constructor) override;
            const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            void PushIndexer(Core::Interfaces::IIndexerDefinition* indexer) override;
            const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            void PushImplicitCast(Core::Interfaces::IFunction* cast) override;
            const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            void PushExplicitCast(Core::Interfaces::IFunction* cast) override;
            const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            void PushOverload(Core::Interfaces::IOperatorOverload* overload) override;
            const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Class() override;
    };

    class ClassSource final : public Class, public Core::UserDefinedType
    {
        public:
            ClassSource(const std::string& name, Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton);

            [[nodiscard]] const std::string& FullName() const override;

            std::vector<const Core::Interfaces::ICharacteristic*> AllCharacteristics() const override;
    };
}

#endif
