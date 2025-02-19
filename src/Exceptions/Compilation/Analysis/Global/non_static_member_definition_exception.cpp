#include "non_static_member_definition_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    NonStaticMemberDefinitionException::NonStaticMemberDefinitionException(const unsigned long index, const SourceFile* const source) : LogException("Static structures cannot define indexers, overloads or constructors.", index, source)
    { }
}

