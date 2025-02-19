#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class Constructor final : public Creation::ConstructorDefinition, public Core::FullyNameable, public Core::Scoped
    {
        public:
            Constructor(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const std::string& SignatureString() const override;
            [[nodiscard]] const std::string& ArgumentSignatureString() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
