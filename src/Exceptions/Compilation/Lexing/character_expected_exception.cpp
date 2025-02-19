#include "character_expected_exception.h"

#include <format>

using namespace Analysis::Structure;

namespace Exceptions
{
    CharacterExpectedException::CharacterExpectedException(const char c, const unsigned long index, const SourceFile* const source) : LogException(std::format("Character: {} expected", c), index, source)
    { }
}
