#ifndef REFERENCED_H
#define REFERENCED_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"

namespace Analysis::Structure::Wrappers
{
    class Referenced final : public DataTypes::Class, public Services::SingletonCollection
    {
        private:
            mutable std::string referenceName;
            const DataType* referencedType;

            explicit Referenced(const DataType* referencedType);

        public:
            static const Referenced* Instance(const DataType* dataType);

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const Core::Characteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Creation::FunctionDefinition* FindFunction(const std::string& name, const std::vector<const DataType*>& argumentList) const override;

            [[nodiscard]] const Creation::ConstructorDefinition* FindConstructor(const std::vector<const DataType*>& argumentList) const override;

            [[nodiscard]] const Creation::IndexerDefinition* FindIndexer(const std::vector<const DataType*>& argumentList) const override;

            [[nodiscard]] const Creation::CastDefinition* FindImplicitCast(const DataType* returnType, const DataType* fromType) const override;
            [[nodiscard]] const Creation::CastDefinition* FindExplicitCast(const DataType* returnType, const DataType* fromType) const override;

            [[nodiscard]] const Creation::OverloadDefinition* FindOverload(Tokens::Enums::SyntaxKind base) const override;
    };
}

#endif
