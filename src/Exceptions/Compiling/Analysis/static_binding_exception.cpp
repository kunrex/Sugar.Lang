#include "static_binding_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    StaticBindingException::StaticBindingException(const string& name, const unsigned long index, const SourceFile* source) : LogException(std::format("Structure {} can only define static members.", name), index, source)
    { }
}

