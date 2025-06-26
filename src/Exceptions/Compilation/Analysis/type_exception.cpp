#include "type_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure;

namespace Exceptions
{
    TypeNotFoundException::TypeNotFoundException(const IParseNode* const parseNode, const SourceFile* const source) : LogException("Failed to reference type", parseNode->Token().Index(), source)
    { }
}

