#include "non_static_member_definition_exception.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    NonStaticMemberDefinitionException::NonStaticMemberDefinitionException(const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException("Static structures cannot define indexers, overloads or constructors.", parseNode, dataType)
    { }
}

