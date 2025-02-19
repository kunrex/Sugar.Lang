#include "parsing_exception.h"

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    ParsingException::ParsingException(const std::string& message, const Token& token, const SourceFile* const source) : LogException(message, token.Index(), source)
    { }
}
