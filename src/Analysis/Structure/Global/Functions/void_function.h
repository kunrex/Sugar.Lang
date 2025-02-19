#ifndef VOID_FUNCTION_H
#define VOID_FUNCTION_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/void_definition.h"

namespace Analysis::Structure::Global
{
    class VoidFunction final : public Creation::VoidDefinition, public Core::Scoped
    {
        public:
            VoidFunction(const std::string& name, Enums::Describer describer, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const std::string& SignatureString() const override;
            [[nodiscard]] const std::string& ArgumentSignatureString() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
