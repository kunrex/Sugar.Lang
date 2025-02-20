#ifndef METHOD_FUNCTION_H
#define METHOD_FUNCTION_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/method_definition.h"

namespace Analysis::Structure::Global
{
    class MethodFunction final : public Creation::MethodDefinition, public Core::Scoped
    {
        public:
            MethodFunction(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
