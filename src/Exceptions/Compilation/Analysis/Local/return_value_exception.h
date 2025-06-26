#ifndef RETURN_VALUE_EXCEPTION_H
#define RETURN_VALUE_EXCEPTION_H
#include "../binding_exception.h"


namespace Exceptions
{
    class ReturnValueException final : public BindingException
    {
        public:
            ReturnValueException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
