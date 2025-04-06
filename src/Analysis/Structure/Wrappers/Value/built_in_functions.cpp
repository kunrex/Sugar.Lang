#include "built_in_functions.h"

#include "boolean.h"
#include "short.h"
#include "long.h"
#include "integer.h"
#include "float.h"
#include "double.h"

namespace Analysis::Structure::Wrappers
{
    template <typename TType>
    CompilationResult ShortCast(const CompilationResult& argument)  { return { &Short::Instance(), static_cast<short>(std::get<TType>(argument.data)) }; }

    template <typename TType>
    CompilationResult IntCast(const CompilationResult& argument) { return { &Integer::Instance(), static_cast<int>(std::get<TType>(argument.data)) }; }

    template <typename TType>
    CompilationResult LongCast(const CompilationResult& argument) { return { &Long::Instance(), static_cast<long>(std::get<TType>(argument.data)) }; }

    template <typename TType>
    CompilationResult FloatCast(const CompilationResult& argument) { return { &Float::Instance(), static_cast<float>(std::get<TType>(argument.data)) }; }

    template <typename TType>
    CompilationResult DoubleCast(const CompilationResult& argument) { return { &Double::Instance(), static_cast<double>(std::get<TType>(argument.data)) }; }

    template <typename TType>
    CompilationResult StringCast(const CompilationResult& argument) { return { &Double::Instance(), std::to_string(std::get<TType>(argument.data)) }; }

    template <typename TType>
    CompilationResult Equals(const std::vector<CompilationResult>& arguments) { return { Boolean::Instance(), std::get<TType>(arguments[0].data) == std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult NotEquals(const std::vector<CompilationResult>& arguments) { return { Boolean::Instance(), std::get<TType>(arguments[0].data) == std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult GreaterThan(const std::vector<CompilationResult>& arguments) { return { Boolean::Instance(), std::get<TType>(arguments[0].data) > std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult LesserThan(const std::vector<CompilationResult>& arguments) { return { Boolean::Instance(), std::get<TType>(arguments[0].data) < std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult GreaterThanEquals(const std::vector<CompilationResult>& arguments) { return { Boolean::Instance(), std::get<TType>(arguments[0].data) >= std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult LesserThanEquals(const std::vector<CompilationResult>& arguments) { return { Boolean::Instance(), std::get<TType>(arguments[0].data) <= std::get<TType>(arguments[1].data)}; }

}