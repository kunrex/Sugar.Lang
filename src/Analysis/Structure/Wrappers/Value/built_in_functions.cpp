#include "built_in_functions.h"

#include "boolean.h"
#include "short.h"
#include "long.h"
#include "integer.h"
#include "./float.h"
#include "double.h"

using namespace std;

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
    CompilationResult Equals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), std::get<TType>(arguments[0].data) == std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult NotEquals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), std::get<TType>(arguments[0].data) == std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult GreaterThan(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), std::get<TType>(arguments[0].data) > std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult LesserThan(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), std::get<TType>(arguments[0].data) < std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult GreaterThanEquals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), std::get<TType>(arguments[0].data) >= std::get<TType>(arguments[1].data)}; }

    template <typename TType>
    CompilationResult LesserThanEquals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), std::get<TType>(arguments[0].data) <= std::get<TType>(arguments[1].data)}; }

    template CompilationResult ShortCast<bool>(const CompilationResult&);
    template CompilationResult ShortCast<char>(const CompilationResult&);
    template CompilationResult ShortCast<int>(const CompilationResult&);
    template CompilationResult ShortCast<long>(const CompilationResult&);
    template CompilationResult ShortCast<float>(const CompilationResult&);
    template CompilationResult ShortCast<double>(const CompilationResult&);

    template CompilationResult IntCast<bool>(const CompilationResult&);
    template CompilationResult IntCast<char>(const CompilationResult&);
    template CompilationResult IntCast<short>(const CompilationResult&);
    template CompilationResult IntCast<long>(const CompilationResult&);
    template CompilationResult IntCast<float>(const CompilationResult&);
    template CompilationResult IntCast<double>(const CompilationResult&);

    template CompilationResult LongCast<bool>(const CompilationResult&);
    template CompilationResult LongCast<char>(const CompilationResult&);
    template CompilationResult LongCast<short>(const CompilationResult&);
    template CompilationResult LongCast<int>(const CompilationResult&);
    template CompilationResult LongCast<float>(const CompilationResult&);
    template CompilationResult LongCast<double>(const CompilationResult&);

    template CompilationResult FloatCast<short>(const CompilationResult&);
    template CompilationResult FloatCast<int>(const CompilationResult&);
    template CompilationResult FloatCast<long>(const CompilationResult&);
    template CompilationResult FloatCast<double>(const CompilationResult&);

    template CompilationResult DoubleCast<short>(const CompilationResult&);
    template CompilationResult DoubleCast<int>(const CompilationResult&);
    template CompilationResult DoubleCast<long>(const CompilationResult&);
    template CompilationResult DoubleCast<float>(const CompilationResult&);

    template CompilationResult StringCast<bool>(const CompilationResult&);
    template CompilationResult StringCast<char>(const CompilationResult&);
    template CompilationResult StringCast<short>(const CompilationResult&);
    template CompilationResult StringCast<int>(const CompilationResult&);
    template CompilationResult StringCast<long>(const CompilationResult&);
    template CompilationResult StringCast<float>(const CompilationResult&);
    template CompilationResult StringCast<double>(const CompilationResult&);

    template CompilationResult Equals<bool>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<char>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<short>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<int>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<long>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<float>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<double>(const std::vector<CompilationResult>& arguments);
    template CompilationResult Equals<string>(const std::vector<CompilationResult>& arguments);

    template CompilationResult NotEquals<bool>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<char>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<short>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<int>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<long>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<float>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<double>(const std::vector<CompilationResult>& arguments);
    template CompilationResult NotEquals<string>(const std::vector<CompilationResult>& arguments);

    template CompilationResult GreaterThan<short>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThan<int>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThan<long>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThan<float>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThan<double>(const std::vector<CompilationResult>& arguments);

    template CompilationResult LesserThan<short>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThan<int>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThan<long>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThan<float>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThan<double>(const std::vector<CompilationResult>& arguments);

    template CompilationResult GreaterThanEquals<short>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThanEquals<int>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThanEquals<long>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThanEquals<float>(const std::vector<CompilationResult>& arguments);
    template CompilationResult GreaterThanEquals<double>(const std::vector<CompilationResult>& arguments);

    template CompilationResult LesserThanEquals<short>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThanEquals<int>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThanEquals<long>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThanEquals<float>(const std::vector<CompilationResult>& arguments);
    template CompilationResult LesserThanEquals<double>(const std::vector<CompilationResult>& arguments);
}