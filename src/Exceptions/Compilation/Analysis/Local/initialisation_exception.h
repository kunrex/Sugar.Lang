#ifndef INITIALISATION_EXCEPTION_H
#define INITIALISATION_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class InitialisationException final : public LogException
    {
        public:
            InitialisationException(const Analysis::Structure::Core::Interfaces::IDataType* expected, const Analysis::Structure::Core::Interfaces::IDataType* actual, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
