#ifndef FUNCTION_ARGUMENT_H
#define FUNCTION_ARGUMENT_H

#include "local_variable.h"

namespace Analysis::Structure::Local
{
    class FunctionParameter final : public LocalVariable
    {
        public:
            FunctionParameter(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;
    };
}

#endif
