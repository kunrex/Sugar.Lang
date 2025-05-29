#ifndef ARRAY_H
#define ARRAY_H

#include "../../../../Services/singleton_service.h"


#include "../../DataTypes/class.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_constructor.h"
#include "../../Core/Interfaces/DataTypes/i_collection_type.h"

namespace Analysis::Structure::Wrappers
{
    class Array final : public DataTypes::BuiltInClass, public Services::SingletonService, public virtual Core::Interfaces::ICollectionType
    {
        private:
            mutable std::string genericSignature;

            const IDataType* arrayType;

            Global::BuiltInProperty* length;

            Global::BuiltInConstructor* constructor;

            Global::BuiltInIndexer* indexer;
        
            explicit Array(const IDataType* arrayType);

        public:
            static const Array* Instance(const IDataType* dataType);

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const IDataType* GenericType() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Array() override;
    };
}

#endif
