#ifndef COMPILATION_RESULT_H
#define COMPILATION_RESULT_H

#include <variant>

#include "../Core/Interfaces/DataTypes/i_primitive_type.h"

namespace Analysis::Structure::Compilation
{
    struct CompilationResult
    {
        public:
            const Core::Interfaces::IPrimitiveType* creationType;
            const std::variant<long, double, std::string> data;

            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, long data);
            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, double data);
            CompilationResult(const Core::Interfaces::IPrimitiveType*, const std::string& data);
            CompilationResult(const Core::Interfaces::IPrimitiveType*, const std::variant<long, double, std::string>& data);
    };
}

#endif
