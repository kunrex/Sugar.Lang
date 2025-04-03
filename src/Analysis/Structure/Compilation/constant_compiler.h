#ifndef CONSTANT_COMPILER_H
#define CONSTANT_COMPILER_H

#include <optional>

#include "compilation_result.h"

#include "../source_file.h"
#include "../Core/Interfaces/Creation/i_constant.h"

namespace Analysis::Structure::Compilation
{
    void CompileExpression(const Core::Interfaces::IConstant* constant, const Core::Interfaces::IDataType* dataType);
}

#endif
