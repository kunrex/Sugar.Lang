#ifndef INVALID_DESCRIBER_EXCEPTION_H
#define INVALID_DESCRIBER_EXCEPTION_H

#include "../../log_exception.h"

#include "../../../Analysis/Structure/Enums/describer.h"

namespace Exceptions
{
    class ExpectedDescriberException final : public LogException
    {
        public:
            ExpectedDescriberException(Analysis::Structure::Enums::Describer value, unsigned long index, const Analysis::Structure::SourceFile* source);
    };

    class InvalidDescriberException final : public LogException
    {
        public:
            InvalidDescriberException(Analysis::Structure::Enums::Describer value, Analysis::Structure::Enums::Describer expected, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
