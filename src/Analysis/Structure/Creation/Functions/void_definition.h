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
            [[nodiscard]] bool Readable() const override;
    };
}

#endif
