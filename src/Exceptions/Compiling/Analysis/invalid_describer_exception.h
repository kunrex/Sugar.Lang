#ifndef INVALID_DESCRIBER_EXCEPTION_H
#define INVALID_DESCRIBER_EXCEPTION_H

#include "../../compile_exception.h"
#include "../../../Analysis/Structure/source_file.h"
#include "../../../Analysis/Structure/Enums/describer.h"

namespace Exceptions
{
    class InvalidDescriberException final : public CompileException
    {
        public:
            InvalidDescriberException(Analysis::Structure::Enums::Describer value, Analysis::Structure::Enums::Describer expected, const Analysis::Structure::SourceFile* source);
    };
}

#endif
