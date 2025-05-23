#ifndef BUILT_IN_METHOD_H
#define BUILT_IN_METHOD_H

#include "../../Core/built_in_function.h"
#include "../../Creation/Functions/method_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInMethod final : public Creation::MethodDefinition, public Core::BuiltInFunction
    {
        public:
            BuiltInMethod(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;
    };
}

#endif
