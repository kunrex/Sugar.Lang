#ifndef BUILT_IN_VOID_H
#define BUILT_IN_VOID_H

#include "../../Creation/Functions/void_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInVoid final : public Creation::VoidDefinition
    {
        public:
            BuiltInVoid(const std::string& name, Enums::Describer describer);
    };
}

#endif
