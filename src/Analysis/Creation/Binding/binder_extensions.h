#ifndef BINDER_EXTENSIONS_H
#define BINDER_EXTENSIONS_H

#include "../../../Exceptions/log_exception.h"

#include "../../Structure/Core/DataTypes/data_type.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_primitive_type.h"

namespace Analysis::Creation::Binding
{
    void PushException(const Exceptions::LogException* exception);

    void ValidateDescriber(const Structure::Core::Describable* describable, Structure::Enums::Describer allowed, unsigned long index, const Structure::SourceFile* source);

    const Structure::Core::Interfaces::IDataType* BindDataType(const ParseNodes::Core::Interfaces::IParseNode* node, const Structure::SourceFile* source);
}

#endif
