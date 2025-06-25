#ifndef COMPILATION_RESULT_H
#define COMPILATION_RESULT_H

#include <variant>

#include "../Core/Interfaces/DataTypes/i_primitive_type.h"

namespace Analysis::Structure::Compilation
{
    typedef std::variant<short, int, long, float, double, char, bool, std::string> Primitive;

    struct CompilationResult
    {
        public:
            const Core::Interfaces::IPrimitiveType* creationType;
            const Primitive data;

            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, short data);
            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, long data);
            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, int data);

            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, char data);
            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, bool data);

            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, float data);
            CompilationResult(const Core::Interfaces::IPrimitiveType* creationType, double data);

            CompilationResult(const Core::Interfaces::IPrimitiveType*, std::string data);

            CompilationResult(const Core::Interfaces::IPrimitiveType*, Primitive data);
    };
}

#endif
