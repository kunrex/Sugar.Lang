#ifndef FUNCTION_EXTENSIONS_H
#define FUNCTION_EXTENSIONS_H

#include "../../binary_context_node.h"

namespace Analysis::Structure::Context
{
    int CalculateFunctionCallSlotSize(const BinaryContextNode* binaryContext);
    int CalculateFunctionCallSlotSize(const DynamicContextCollection* function);
}

#endif
