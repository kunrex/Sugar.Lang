#ifndef SHORT_H
#define SHORT_H

#include <map>

#include "../../../../Services/singleton_service.h"

#include "../../Core/Interfaces/Creation/i_built_in_cast.h"
#include "../../Core/Interfaces/DataTypes/i_primitive_type.h"

#include "../../DataTypes/value_type.h"
#include "../../Global/BuiltIn/built_in_method.h"

namespace Analysis::Structure::Wrappers
{
    class Short final : public DataTypes::BuiltInValueType, public Services::SingletonService, public virtual Core::Interfaces::IPrimitiveType
    {
        private:
            std::map<std::string, const Core::Interfaces::ICharacteristic*> characteristics;

            Global::BuiltInMethod* tryParse;

            std::map<unsigned long, const Core::Interfaces::IFunction*> implicitCasts;
            std::map<unsigned long, const Core::Interfaces::IBuiltInCast*> explicitCasts;

            std::map<Tokens::Enums::SyntaxKind, const Core::Interfaces::IBuiltInOverload*> overloads;

            Short();

        public:
            static const Short& Instance();

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;

            void InitializeMembers() override;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const override;
            [[nodiscard]] const Core::Interfaces::IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IBuiltInCast* FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            [[nodiscard]] const Core::Interfaces::IBuiltInOverload* FindBuiltInOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Short() override;
    };
}

#endif
