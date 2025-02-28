#ifndef FUNCTION_EXTENSIONS_H
#define FUNCTION_EXTENSIONS_H

#include "../../binary_context_node.h"
#include "../../context_node.h"
#include "../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    int CalculateFunctionCallSlotSize(const BinaryContextNode* binaryContext);
    int CalculateFunctionCallSlotSize(const Services::ConstantCollection<ContextNode>* function);
}

#endif
