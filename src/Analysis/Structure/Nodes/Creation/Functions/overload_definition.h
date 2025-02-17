#ifndef OVERLOAD_DEFINITION_H
#define OVERLOAD_DEFINITION_H

#include "../../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class OverloadDefinition : public Core::Function
    {
        protected:
            const Tokens::Enums::SyntaxKind baseOperator;

            OverloadDefinition(Tokens::Enums::SyntaxKind baseOperator, Enums::Describer describer, const Core::DataType* creationType);

        public:
            [[nodiscard]] Tokens::Enums::SyntaxKind Operator() const;
    };
}

#endif
