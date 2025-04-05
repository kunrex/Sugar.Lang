#ifndef CONSTANT_COMPILER_H
#define CONSTANT_COMPILER_H

#include "../source_file.h"

#include "../Core/Interfaces/Creation/i_constant.h"

namespace Analysis::Structure::Compilation
{
    void CompileExpression(const Core::Interfaces::IConstant* constant, const Core::Interfaces::IUserDefinedType* dataType);
}

#endif
