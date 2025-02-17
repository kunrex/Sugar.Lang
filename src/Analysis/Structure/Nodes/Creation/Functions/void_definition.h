#ifndef VOID_DEFINITION_H
#define VOID_DEFINITION_H

#include "function_definition.h"

namespace Analysis::Structure::Creation
{
    class VoidDefinition : public FunctionDefinition
    {
        protected:
            VoidDefinition(const std::string& name, Enums::Describer describer);

        public:
            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] bool Readable() const override;

            [[nodiscard]] const std::string& FullName() const override;
            [[nodiscard]] const std::string& SignatureString() const override;;
    };
}

#endif
