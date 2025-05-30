#ifndef LIST_H
#define LIST_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Core/Interfaces/DataTypes/i_collection_type.h"

namespace Analysis::Structure::Wrappers
{
    class List final : public DataTypes::BuiltInClass, public Services::SingletonService, public virtual Core::Interfaces::ICollectionType
    {
        private:
            mutable std::string genericSignature;

            const IDataType* listType;

            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

            std::vector<std::tuple<unsigned long, const Core::Interfaces::IFunctionDefinition*>> functions;

            std::vector<std::tuple<unsigned long, const Core::Interfaces::IConstructor*>> constructors;

            Global::BuiltInIndexer* indexer;

            explicit List(const IDataType* listType);

        public:
            static const List* Instance(const IDataType* dataType);

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

            ~List() override;
    };
}

#endif
