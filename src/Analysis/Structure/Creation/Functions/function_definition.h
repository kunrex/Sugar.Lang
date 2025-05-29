#ifndef FUNCTION_DEFINITION_H
#define FUNCTION_DEFINITION_H

#include "../../Core/nameable.h"
#include "../../Core/Creation/function.h"

#include "../../Core/Interfaces/Creation/i_function_definition.h"

namespace Analysis::Structure::Creation
{
    class FunctionDefinition : public Core::Nameable, public Core::Function, public virtual Core::Interfaces::IFunctionDefinition
    {
        protected:
            mutable std::string signature;

            FunctionDefinition(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] const std::string& Signature() const override;
    };
}

#endif
