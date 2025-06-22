#ifndef OBJECT_H
#define OBJECT_H

#include <array>

#include "../../DataTypes/class.h"

#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Object final : public DataTypes::ImplicitClass, public Services::SingletonService
    {
        private:
            static Object instance;

            std::array<std::pair<Tokens::Enums::SyntaxKind, const Core::Interfaces::IOperatorOverload*>, 2> overloads;

            Object();

        public:
            static const Object* Instance();
            static void BindGlobalInstance();

            void BindGlobal() override;

            [[nodiscard]] Tokens::Enums::TypeKind Type() const override;;

            [[nodiscard]] const Core::Interfaces::ICharacteristic* FindCharacteristic(const std::string& name) const override;

            [[nodiscard]] const Core::Interfaces::IConstructor* FindConstructor(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const override;

            [[nodiscard]] const Core::Interfaces::IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const override;

            ~Object() override;
    };

}

#endif
