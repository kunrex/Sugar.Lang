#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class Constructor final : public Creation::ConstructorDefinition, public Core::Scoped, public Core::FullyNameable
    {
        public:
            Constructor(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
            [[nodiscard]] const std::string& SignatureString() const override;

            void AddArgument(const Creation::Variable* parameter) override;
    };
}

#endif
