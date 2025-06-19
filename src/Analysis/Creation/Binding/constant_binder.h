#ifndef CONSTANT_BINDER_H
#define CONSTANT_BINDER_H

#include "../../Structure/Core/Interfaces/Context/i_context_node.h"
#include "../../Structure/Core/Interfaces/Creation/i_characteristic.h"
#include "../../Structure/Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Analysis::Creation::Binding
{
    const Structure::Core::Interfaces::IContextNode* ConstantCompile(Structure::Core::Interfaces::ICharacteristic* characteristic, const Structure::Core::Interfaces::IUserDefinedType* dataType);
    const Structure::Core::Interfaces::IContextNode* VariableCompile(Structure::Core::Interfaces::ICharacteristic* characteristic, const Structure::Core::Interfaces::IUserDefinedType* dataType);
}

#endif
