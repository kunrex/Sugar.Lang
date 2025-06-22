#ifndef ARRAY_H
#define ARRAY_H

#include "../../DataTypes/class.h"

#include "../../Core/Interfaces/DataTypes/i_collection_type.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Array final : public DataTypes::ImplicitClass, public Services::SingletonService, public virtual Core::Interfaces::ICollectionType
    {
        private:
            mutable std::string genericSignature;

            const IDataType* arrayType;

            const Core::Interfaces::ICharacteristic* length;

            const Core::Interfaces::IConstructor* constructor;

            const Core::Interfaces::IIndexerDefinition* indexer;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;
        
            explicit Array(const IDataType* arrayType);

        public:
            static const Array* Instance(const IDataType* dataType);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const IDataType* GenericType() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Array() override;
    };
}

#endif
