#ifndef BUILT_IN_VOID_H
#define BUILT_IN_VOID_H

#include "../../Core/built_in_function.h"
#include "../../Creation/Functions/void_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInVoid final : public Creation::VoidDefinition, public Core::BuiltInFunction
    {
        public:
            BuiltInVoid(const std::string& name, Enums::Describer describer, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };
}

#endif
