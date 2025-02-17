#ifndef METHOD_DEFINITION_H
#define METHOD_DEFINITION_H

#include "function_definition.h"

namespace Analysis::Structure::Creation
{
    class MethodDefinition : public FunctionDefinition
    {
        protected:
            MethodDefinition(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);

        public:
            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
            [[nodiscard]] const std::string& SignatureString() const override;
    };
}

#endif
