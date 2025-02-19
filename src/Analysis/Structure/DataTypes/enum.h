#ifndef ENUM_H
#define ENUM_H

#include <map>

#include "../Core/DataTypes/data_type.h"
#include "../Core/DataTypes/user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class Enum final : public Core::DataType, public Core::UserDefinedType
    {
        protected:
            std::map<std::string, Core::Characteristic*> characteristics;

        public:
            Enum(const std::string& name, Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton);

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

            ~Enum() override;
    };
}

#endif
