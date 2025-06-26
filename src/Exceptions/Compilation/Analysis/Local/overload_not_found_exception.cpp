#include "overload_not_found_exception.h"

#include <format>

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    OverloadNotFoundException::OverloadNotFoundException(const SyntaxKind kind, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException(std::format("No overload found for: {}", ToString(kind)), parseNode, dataType)
    { }
}
