#ifndef COMPILATION_RESULT_H
#define COMPILATION_RESULT_H

#include <variant>

#include "../Core/Interfaces/DataTypes/i_data_type.h"

namespace Analysis::Structure::Compilation
{
    struct CompilationResult
    {
        public:
            const Tokens::Enums::TypeKind creationType;
            const std::variant<long, double, std::string> data;

            CompilationResult(Tokens::Enums::TypeKind creationType, long data);
            CompilationResult(Tokens::Enums::TypeKind creationType, double data);
            CompilationResult(Tokens::Enums::TypeKind creationType, const std::string& data);
            CompilationResult(Tokens::Enums::TypeKind creationType, std::variant<long, double, std::string>& data);
    };
}

#endif
