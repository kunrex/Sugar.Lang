#ifndef BINDER_EXTENSIONS_H
#define BINDER_EXTENSIONS_H

#include "../../../Exceptions/log_exception.h"

#include "../../Structure/Core/DataTypes/data_type.h"

namespace Analysis::Creation::Binding
{
    void PushException(const Exceptions::LogException* exception);

    void MatchDescriber(const Structure::Core::Describable* describable, Structure::Enums::Describer expected, unsigned long index, const Structure::SourceFile* source);
    void ValidateDescriber(const Structure::Core::Describable* describable, Structure::Enums::Describer allowed, unsigned long index, const Structure::SourceFile* source);

    const Structure::Core::DataType* BindDataType(const ParseNodes::ParseNode* node, const Structure::SourceFile* source);
}

#endif
