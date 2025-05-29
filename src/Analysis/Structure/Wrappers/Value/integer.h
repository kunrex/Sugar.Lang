#ifndef INTEGER_H
#define INTEGER_H

#include <tuple>
#include <vector>

#include "../../../../Services/singleton_service.h"

#include "../../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../../Core/Interfaces/DataTypes/i_primitive_type.h"

#include "../../DataTypes/value_type.h"
#include "../../Global/BuiltIn/built_in_method.h"

namespace Analysis::Structure::Wrappers
{
    class Integer final : public DataTypes::BuiltInValueType, public Services::SingletonService, public virtual Core::Interfaces::IPrimitiveType
    {
        private:
            static Integer instance;

            Global::BuiltInMethod* tryParse;

            std::vector<std::tuple<unsigned long, const Core::Interfaces::IFunction*>> implicitCasts;
            std::vector<std::tuple<unsigned long, const Core::Interfaces::IBuiltInCast*>> explicitCasts;

            std::vector<std::tuple<Tokens::Enums::SyntaxKind, const Core::Interfaces::IBuiltInOverload*>> overloads;

            Integer();

        public:
            static const Integer* Instance();
            static void BindGlobalInstance();

            [[nodiscard]] int SlotCount() const override;

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

            ~Integer() override;
    };
}

#endif
