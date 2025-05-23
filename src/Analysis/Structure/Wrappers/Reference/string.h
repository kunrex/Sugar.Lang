#ifndef STRING_H
#define STRING_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../Core/Interfaces/DataTypes/i_primitive_type.h"
#include "../../Core/Interfaces/Creation/i_built_in_overload.h"

#include "../../DataTypes/class.h"
#include "../../Global/BuiltIn/built_in_indexer.h"

namespace Analysis::Structure::Wrappers
{
    class String final : public DataTypes::BuiltInClass, public Services::SingletonService, public virtual Core::Interfaces::IPrimitiveType
    {
        private:
            std::map<std::string, const Core::Interfaces::ICharacteristic*> characteristics;

            std::map<unsigned long, const Core::Interfaces::IFunctionDefinition*> functions;

            Global::BuiltInIndexer* indexer;

            std::map<Tokens::Enums::SyntaxKind, const Core::Interfaces::IBuiltInOverload*> overloads;

            String();

        public:
            static const String& Instance();

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(bool isStatic, const std::vector<const IDataType*>& argumentList) const override;

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
