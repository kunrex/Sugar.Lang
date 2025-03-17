#ifndef CONSTANT_COMPILER_H
#define CONSTANT_COMPILER_H

#include <optional>

#include "compilation_result.h"

#include "../source_file.h"

namespace Analysis::Structure::Compilation
{
    std::optional<CompilationResult> CompileExpression(const ParseNodes::ParseNode* expressionNode, const SourceFile* source);
}

#endif
