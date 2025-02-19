#ifndef REFERENCED_H
#define REFERENCED_H

#include "../../Core/DataTypes/data_type.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Referenced final : public Core::DataType, public Services::SingletonCollection
    {
        private:
            mutable int slotCount;
            const DataType* referencedType;

            explicit Referenced(const DataType* nullableType);

        public:
            static const Referenced* Instance(const DataType* dataType);

            [[nodiscard]] int SlotCount() const override;
            [[nodiscard]] Enums::MemberType MemberType() const override;

            const Core::Characteristic* FindCharacteristic(const std::string& name) const override;
            void PushCharacteristic(Core::Characteristic* characteristic) override;

            const Creation::ConstructorDefinition* FindConstructor(const std::vector<const DataType*>& argumentList) const override;
            void PushConstructor(Creation::ConstructorDefinition* constructor) override;

            const Creation::FunctionDefinition* FindFunction(const std::string& name, const std::vector<const DataType*>& argumentList) const override;
            void PushFunction(Creation::FunctionDefinition* function) override;

            const Creation::IndexerDefinition* FindIndexer(const std::vector<const DataType*>& argumentList) const override;
            void PushIndexer(Creation::IndexerDefinition* indexer) override;

            void PushExplicitCast(Creation::CastDefinition* cast) override;
            const Creation::CastDefinition* FindExplicitCast(const DataType* returnType, const DataType* fromType) const override;

            void PushImplicitCast(Creation::CastDefinition* cast) override;
            const Creation::CastDefinition* FindImplicitCast(const DataType* returnType, const DataType* fromType) const override;

            void PushOverload(Creation::OverloadDefinition* overload) override;
            const Creation::OverloadDefinition* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            std::vector<Core::Characteristic*> AllCharacteristics() const override;
            std::vector<Core::Scoped*> AllFunctions() const override;
    };
}

#endif
