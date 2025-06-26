#ifndef BINDER_EXTENSIONS_H
#define BINDER_EXTENSIONS_H

#include "../../Structure/source_file.h"
#include "../../Structure/Core/describable.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_data_type.h"

namespace Analysis::Creation::Binding
{
    void ValidateDescriber(const Structure::Core::Describable* describable, Structure::Enums::Describer allowed, const ParseNodes::Core::Interfaces::IParseNode* parseNode, const Structure::Core::Interfaces::IUserDefinedType* dataType);

    const Structure::Core::Interfaces::IDataType* BindDataType(const ParseNodes::Core::Interfaces::IParseNode* node, const Structure::SourceFile* source);
}

#endif
