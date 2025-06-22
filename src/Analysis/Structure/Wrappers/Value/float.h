#ifndef FLOAT_H
#define FLOAT_H

#include <array>

#include "../../DataTypes/value_type.h"

#include "../../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../../Core/Interfaces/DataTypes/i_primitive_type.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Float final : public DataTypes::BuiltInValueType, public Services::SingletonService, public virtual Core::Interfaces::IPrimitiveType
    {
        private:
            static Float instance;

            std::array<const Core::Interfaces::ICharacteristic*, 6> characteristics;

            std::array<std::pair<unsigned long, const Core::Interfaces::IFunctionDefinition*>, 2> functions;

            const Core::Interfaces::IFunction* implicitDouble;
            std::array<std::pair<unsigned long, const Core::Interfaces::IBuiltInCast*>, 5> explicitCasts;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;
            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IBuiltInOverload*>, 12> builtInOverloads;

            Float();

        public:
            static const Float* Instance();
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

            ~Float() override;
    };
}

#endif
