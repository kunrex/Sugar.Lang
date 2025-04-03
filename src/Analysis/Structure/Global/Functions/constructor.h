#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class Constructor : public Core::Nameable, public Creation::ConstructorDefinition, public Core::Scoped
    {
        public:
            Constructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };

    class DefaultConstructor final : public Constructor
    {
        public:
            explicit DefaultConstructor(const Core::Interfaces::IDataType* creationType);

            ~DefaultConstructor() override;
    };
}

#endif
