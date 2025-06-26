#ifndef CONSTANT_EXPECTED_EXCEPTION_H
#define CONSTANT_EXPECTED_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class ConstantNotFoundException final : public BindingException
    {
        public:
            ConstantNotFoundException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
