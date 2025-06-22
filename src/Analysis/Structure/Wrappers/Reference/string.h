#ifndef STRING_H
#define STRING_H

#include <array>

#include "../../DataTypes/class.h"

#include "../../Core/Interfaces/DataTypes/i_primitive_type.h"
#include "../../Core/Interfaces/Creation/i_built_in_overload.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class String final : public DataTypes::BuiltInClass, public Services::SingletonService, public virtual Core::Interfaces::IPrimitiveType
    {
        private:
            static String instance;

            std::array<const Core::Interfaces::ICharacteristic*, 2> characteristics;

            std::array<std::pair<unsigned long, const Core::Interfaces::IFunctionDefinition*>, 17> functions;

            const Core::Interfaces::IIndexerDefinition* indexer;

            const Core::Interfaces::IFunction* implicitObject;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IBuiltInOverload*>, 4> overloads;

            String();

        public:
            static const String* Instance();
            static void BindGlobalInstance();

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IBuiltInCast* FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            [[nodiscard]] const Core::Interfaces::IBuiltInOverload* FindBuiltInOverload(Tokens::Enums::SyntaxKind base) const override;

            ~String() override;
    };
}

#endif
