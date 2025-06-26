#ifndef I_FUNCTION_DEFINITION_H
#define I_FUNCTION_DEFINITION_H

#include "i_function.h"

#include "../i_nameable.h"
#include "../i_bindable.h"
#include "../i_transpilable.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IFunctionDefinition : public virtual INameable, public virtual IFunction, public virtual ILocallyBindable, public virtual ITranspilable
    {
        public:
            [[nodiscard]] virtual const std::string& Signature() const = 0;
    };
}

#endif
