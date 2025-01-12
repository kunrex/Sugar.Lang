#include "invalid_expression_exception.h"

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidExpressionException::InvalidExpressionException(const Token& token, const SourceFile* source) : ParsingException("Invalid expression", token, source)
    { }
}
