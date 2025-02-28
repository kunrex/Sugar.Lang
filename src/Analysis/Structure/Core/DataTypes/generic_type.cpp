#include "generic_type.h"

namespace Analysis::Structure::Core
{
    GenericType::GenericType() = default;

    const std::string& GenericType::GenericSignature() const { return genericSignature; }
}