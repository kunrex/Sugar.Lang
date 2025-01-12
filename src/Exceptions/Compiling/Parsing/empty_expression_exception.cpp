#include "empty_expression_exception.h"

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    EmptyExpressionException::EmptyExpressionException(const Token& token, const SourceFile* source) : ParsingException("Expected non empty expression", token, source)
    { }
}
