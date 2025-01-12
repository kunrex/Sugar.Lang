#ifndef CHARACTER_EXPECTED_EXCEPTION_H
#define CHARACTER_EXPECTED_EXCEPTION_H

#include "../../log_exception.h"
#include "../../../Analysis/Structure/source_file.h"

namespace Exceptions
{
    class CharacterExpectedException final : public LogException
    {
        public:
            explicit CharacterExpectedException(char c, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
