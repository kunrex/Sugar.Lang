#ifndef BINDER_EXTENSIONS_H
#define BINDER_EXTENSIONS_H

#include "../../Structure/Core/DataTypes/data_type.h"

namespace Analysis::Creation::Binding
{
    const Structure::Core::DataType* BindDataType(const ParseNodes::ParseNode* node, const Structure::SourceFile* source);

    void MatchStaticBindings(const Structure::Core::Describable* describable, const Structure::Core::DataType* dataType, unsigned long index);
}

#endif
