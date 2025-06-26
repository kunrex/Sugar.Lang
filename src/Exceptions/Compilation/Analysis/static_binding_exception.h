#ifndef STATIC_BINDING_EXCEPTION_H
#define STATIC_BINDING_EXCEPTION_H

#include "binding_exception.h"

namespace Exceptions
{
    class StaticBindingException final : public BindingException
    {
        public:
            StaticBindingException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
