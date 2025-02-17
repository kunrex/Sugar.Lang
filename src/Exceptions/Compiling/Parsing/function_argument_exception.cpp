#include "function_argument_exception.h"

#include <format>

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    FunctionArgumentException::FunctionArgumentException(int argumentCount, const Token& token, const SourceFile* source) : ParsingException(std::format("{} function requires {} argument", ToString(token.Kind()), argumentCount), token, source)
    { }

    MinimumFunctionArgumentException::MinimumFunctionArgumentException(int argumentCount, const Token& token, const SourceFile* source) : ParsingException(std::format("{} function requires at least {} argument", ToString(token.Kind()), argumentCount), token, source)
    { }
}
