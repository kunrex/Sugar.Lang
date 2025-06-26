#include "invalid_describer_exception.h"

#include <format>

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    ExpectedDescriberException::ExpectedDescriberException(const Describer value, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException(std::format("Expected describer {}", ToString(value)), parseNode, dataType)
    { }

    InvalidDescriberException::InvalidDescriberException(const Describer value, const Describer expected, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException(std::format("Allowed describers: {}, instead got: {}", ToString(expected), ToString(value)), parseNode, dataType)
    { }
}
