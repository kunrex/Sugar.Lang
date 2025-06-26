#include "initialisation_exception.h"

#include <format>

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    InitialisationException::InitialisationException(const IDataType* const expected, const IDataType* const actual, const IParseNode* const parseNode, const IUserDefinedType* const dataType) : BindingException(std::format("Value initialised to type of: {}. Expected: {}", actual->FullName(), expected->FullName()), parseNode, dataType)
    { }
}
