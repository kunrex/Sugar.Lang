#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H

#include <map>

#include "../Core/DataTypes/data_type.h"
#include "../Core/DataTypes/user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class ValueType : public Core::DataType
    {
        protected:
            mutable int slotCount;
            mutable std::string fullName;

            std::map<std::string, Core::Characteristic*> characteristics;

            std::map<unsigned long, Creation::FunctionDefinition*> functions;

            std::map<unsigned long, Creation::ConstructorDefinition*> constructors;

            std::map<unsigned long, Creation::IndexerDefinition*> indexers;

            std::map<unsigned long, Creation::CastDefinition*> implicitCasts;
            std::map<unsigned long, Creation::CastDefinition*> explicitCasts;

            std::map<Tokens::Enums::SyntaxKind, Creation::OverloadDefinition*> overloads;

        public:
            ValueType(const std::string& name, Enums::Describer describer);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void PushCharacteristic(Core::Characteristic* characteristic) override;
            const Core::Characteristic* FindCharacteristic(const std::string& name) const override;

            void PushFunction(Creation::FunctionDefinition* function) override;
            const Creation::FunctionDefinition* FindFunction(const std::string& name, const std::vector<const DataType*>& argumentList) const override;

            void PushConstructor(Creation::ConstructorDefinition* constructor) override;
            const Creation::ConstructorDefinition* FindConstructor(const std::vector<const DataType*>& argumentList) const override;

            void PushIndexer(Creation::IndexerDefinition* indexer) override;
            const Creation::IndexerDefinition* FindIndexer(const std::vector<const DataType*>& argumentList) const override;

            void PushImplicitCast(Creation::CastDefinition* cast) override;
            const Creation::CastDefinition* FindImplicitCast(const DataType* returnType, const DataType* fromType) const override;
            void PushExplicitCast(Creation::CastDefinition* cast) override;
            const Creation::CastDefinition* FindExplicitCast(const DataType* returnType, const DataType* fromType) const override;

            void PushOverload(Creation::OverloadDefinition* overload) override;
            const Creation::OverloadDefinition* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            [[nodiscard]] std::vector<const Core::Characteristic*> AllCharacteristics() const override;

            ~ValueType() override;
    };

    class StructSource final : public ValueType, public Core::UserDefinedType
    {
        public:
            StructSource(const std::string& name, Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton);

            [[nodiscard]] const std::string& FullName() const override;
    };
}


#endif
