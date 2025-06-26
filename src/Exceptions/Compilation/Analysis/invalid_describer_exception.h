#ifndef INVALID_DESCRIBER_EXCEPTION_H
#define INVALID_DESCRIBER_EXCEPTION_H

#include "binding_exception.h"

#include "../../../Analysis/Structure/Enums/describer.h"

namespace Exceptions
{
    class ExpectedDescriberException final : public BindingException
    {
        public:
            ExpectedDescriberException(Analysis::Structure::Enums::Describer value, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };

    class InvalidDescriberException final : public BindingException
    {
        public:
            InvalidDescriberException(Analysis::Structure::Enums::Describer value, Analysis::Structure::Enums::Describer expected,  const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Analysis::Structure::Core::Interfaces::IUserDefinedType* dataType);
    };
}

#endif
