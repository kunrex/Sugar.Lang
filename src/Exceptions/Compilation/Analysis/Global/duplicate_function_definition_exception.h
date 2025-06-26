#ifndef DUPLICATE_FUNCTION_DEFINITION_EXCEPTION_H
#define DUPLICATE_FUNCTION_DEFINITION_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class DuplicateFunctionDefinition final : public BindingException
    {
        public:
            DuplicateFunctionDefinition(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
