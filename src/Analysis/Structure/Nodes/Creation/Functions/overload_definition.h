#ifndef OVERLOAD_DEFINITION_H
#define OVERLOAD_DEFINITION_H

#include "../../../../../Lexing/Tokens/token.h"
#include "../../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class OverloadDefinition : public Core::Function, public Core::FullyNameable
    {
        protected:
            const Tokens::Token& baseOperator;

            OverloadDefinition(const Tokens::Token& baseOperator, Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
