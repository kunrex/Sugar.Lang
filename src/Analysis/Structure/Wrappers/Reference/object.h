#ifndef OBJECT_H
#define OBJECT_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Global/BuiltIn/built_in_cast.h"

namespace Analysis::Structure::Wrappers
{
    class Object final : public DataTypes::BuiltInClass, public Services::SingletonService
    {
        private:
            Global::BuiltInCast* toString;

            Object();

        public:
            static const Object* Instance();

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;;

            void BindGlobal() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Object() override;
    };

}

#endif
