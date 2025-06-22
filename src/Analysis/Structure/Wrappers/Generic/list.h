#ifndef LIST_H
#define LIST_H

#include <array>

#include "../../DataTypes/class.h"

#include "../../Core/Interfaces/DataTypes/i_collection_type.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class List final : public DataTypes::BuiltInClass, public Services::SingletonService, public virtual Core::Interfaces::ICollectionType
    {
        private:
            mutable std::string genericSignature;

            const IDataType* listType;

            std::array<const Core::Interfaces::ICharacteristic*, 2> characteristics;

            std::array<std::pair<unsigned long, const Core::Interfaces::IFunctionDefinition*>, 7> functions;

            std::array<std::pair<unsigned long, const Core::Interfaces::IConstructor*>, 2> constructors;

            const Core::Interfaces::IIndexerDefinition* indexer;

            const Core::Interfaces::IFunction* implicitObject;

            const Core::Interfaces::IFunction* explicitString;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;

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
