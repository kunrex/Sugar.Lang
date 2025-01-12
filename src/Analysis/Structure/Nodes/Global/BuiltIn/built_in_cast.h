#ifndef BUILT_IN_CAST_H
#define BUILT_IN_CAST_H

#include "../../Creation/Functions/cast_definition.h"
#include "../../../Core/Context/built_in_instruction.h"

namespace Analysis::Structure::Global
{
    class BuiltInCast final : public Creation::CastDefinition, public Core::BuiltInInstruction
    {
        public:
            BuiltInCast(const Core::DataType* creationType, const std::string& instruction);
    };
}

#endif
