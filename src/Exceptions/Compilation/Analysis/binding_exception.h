#ifndef BINDING_EXCEPTION_H
#define BINDING_EXCEPTION_H


#include "../../log_exception.h"

#include "../../../Parsing/ParseNodes/Core/Interfaces/i_parse_node.h"

#include "../../../Analysis/Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Exceptions
{
    class BindingException : public LogException
    {
        public:
            BindingException(const std::string& message, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
