#ifndef BUILT_IN_FUNCTIONS_H
#define BUILT_IN_FUNCTIONS_H

#include "../../Compilation/compilation_result.h"

using namespace Analysis::Structure::Compilation;

namespace Analysis::Structure::Wrappers
{
    template <typename TType>
    CompilationResult ShortCast(const CompilationResult& argument);

    template <typename TType>
    CompilationResult IntCast(const CompilationResult& argument) ;

    template <typename TType>
    CompilationResult LongCast(const CompilationResult& argument);

    template <typename TType>
    CompilationResult FloatCast(const CompilationResult& argument);

    template <typename TType>
    CompilationResult DoubleCast(const CompilationResult& argument);

    template <typename TType>
    CompilationResult StringCast(const CompilationResult& argument);

    template <typename TType>
    CompilationResult Equals(const std::vector<CompilationResult>& arguments);

    template <typename TType>
    CompilationResult NotEquals(const std::vector<CompilationResult>& arguments);

    template <typename TType>
    CompilationResult GreaterThan(const std::vector<CompilationResult>& arguments);

    template <typename TType>
    CompilationResult LesserThan(const std::vector<CompilationResult>& arguments);

    template <typename TType>
    CompilationResult GreaterThanEquals(const std::vector<CompilationResult>& arguments);

    template <typename TType>
    CompilationResult LesserThanEquals(const std::vector<CompilationResult>& arguments);
}

#endif
