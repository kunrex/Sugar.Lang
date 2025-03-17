#ifndef COMPILATION_RESULT_H
#define COMPILATION_RESULT_H

#include <variant>

#include "../Core/Interfaces/DataTypes/i_data_type.h"

namespace Analysis::Structure::Compilation
{
    struct CompilationResult
    {
        public:
            const TypeCode creationType;
            const std::variant<long, double, std::string> data;

            CompilationResult(TypeCode creationType, long data);
            CompilationResult(TypeCode creationType, double data);
            CompilationResult(TypeCode creationType, const std::string& data);
    };
}

#endif
