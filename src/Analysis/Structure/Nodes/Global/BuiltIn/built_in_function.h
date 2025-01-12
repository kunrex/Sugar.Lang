#ifndef BUILT_IN_FUNCTION_H
#define BUILT_IN_FUNCTION_H

#include "../../../Core/Context/built_in_instruction.h"
#include "../../Creation/Functions/function_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInFunction final : public Creation::FunctionDefinition, public Core::BuiltInInstruction
    {
        public:
            BuiltInFunction(Enums::Describer describer, const std::string& name, const Core::DataType* creationType, const std::string& instruction);
    };
}

#endif
