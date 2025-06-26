#ifndef VARIABLE_DEFINITION_EXCEPTION_H
#define VARIABLE_DEFINITION_EXCEPTION_H

#include "binding_exception.h"

namespace Exceptions
{
    class DuplicateVariableDefinitionException final : public BindingException
    {
        public:
            DuplicateVariableDefinitionException(const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
