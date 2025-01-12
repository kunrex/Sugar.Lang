#ifndef BUILT_IN_OPERATION_H
#define BUILT_IN_OPERATION_H

#include "../../../Core/Context/built_in_instruction.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInOperation final : public Creation::OverloadDefinition, public Core::BuiltInInstruction
    {
        public:
            BuiltInOperation(const Tokens::Token& baseOperator, const Core::DataType* creationType, const std::string& instruction);
    };
}

#endif
