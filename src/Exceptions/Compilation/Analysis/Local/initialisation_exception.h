#ifndef INITIALISATION_EXCEPTION_H
#define INITIALISATION_EXCEPTION_H

#include "../binding_exception.h"

namespace Exceptions
{
    class InitialisationException final : public BindingException
    {
        public:
            InitialisationException(const Analysis::Structure::Core::Interfaces::IDataType* expected, const Analysis::Structure::Core::Interfaces::IDataType* actual, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
