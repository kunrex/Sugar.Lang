#ifndef FUNCTION_DEFINITION_H
#define FUNCTION_DEFINITION_H

#include "../../Core/nameable.h"
#include "../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class FunctionDefinition : public Core::Nameable, public Core::Function
    {
        protected:
            FunctionDefinition(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
