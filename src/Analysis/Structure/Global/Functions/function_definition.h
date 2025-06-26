#ifndef FUNCTION_DEFINITION_H
#define FUNCTION_DEFINITION_H

#include "../../Core/nameable.h"
#include "../../Core/Creation/function.h"
#include "../../Core/Interfaces/Creation/i_function_definition.h"

namespace Analysis::Structure::Global
{
    class FunctionDefinition : public Core::Function, public Core::Nameable, public virtual Core::Interfaces::IFunctionDefinition
    {
        protected:
            mutable std::string signature;

            FunctionDefinition(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] const std::string& Signature() const override;
    };

    class VoidDefinition : public FunctionDefinition
    {
        protected:
            VoidDefinition(const std::string& name, Enums::Describer describer);
    };

    class MethodDefinition : public FunctionDefinition
    {
        protected:
            MethodDefinition(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };
}

#endif
