#ifndef I_OPERATOR_OVERLOAD_H
#define I_OPERATOR_OVERLOAD_H

#include "i_function.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IOperatorOverload : public virtual IFunction
    {
        public:
            [[nodiscard]] virtual Tokens::Enums::SyntaxKind Operator() const = 0;
    };
}

#endif
