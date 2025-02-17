#ifndef BUILT_IN_METHOD_H
#define BUILT_IN_METHOD_H

#include "../../Creation/Functions/method_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInMethod final : public Creation::MethodDefinition
    {
        public:
            BuiltInMethod(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
