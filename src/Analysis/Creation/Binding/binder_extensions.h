#ifndef BINDER_EXTENSIONS_H
#define BINDER_EXTENSIONS_H

#include "../../../Exceptions/log_exception.h"

#include "../../Structure/Core/DataTypes/data_type.h"

namespace Analysis::Creation::Binding
{
    void PushException(const Exceptions::LogException* exception);

    const Structure::Core::Interfaces::IDataType* BindDataType(const ParseNodes::ParseNode* node, const Structure::SourceFile* source);
}

#endif
