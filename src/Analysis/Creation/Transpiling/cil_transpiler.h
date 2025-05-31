#ifndef CIL_TRANSPILER_H
#define CIL_TRANSPILER_H

#include <string>

#include "../../../Services/string_builder.h"

#include "../../Structure/source_file.h"
#include "../../Structure/source_directory.h"
#include "../../Structure/Context/context_node.h"
#include "../../Structure/Core/Interfaces/Scoped/i_scoped.h"
#include "../../Structure/Global/Variables/global_constant.h"

namespace Analysis::Creation::Transpiling
{
    const std::string open_flower = "{";
    const std::string close_flower = "}";

    const std::string pop = "pop";
    const std::string dup = "dup";
    const std::string load_this = "ldarg.0";

    std::string_view AccessModifierString(const Structure::Core::Interfaces::IDescribable* describable);

    std::string_view StaticModifierString(const Structure::Core::Interfaces::IFunction* describable);
    std::string_view StaticModifierString(const Structure::Core::Interfaces::IUserDefinedType* describable);

    std::string ConstantString(const Structure::Core::Interfaces::ICharacteristic* characteristic);

    std::string ScopedParameterString(const Structure::Core::Interfaces::IScoped* function);
    std::string ScopedLocalVariableString(const Structure::Core::Interfaces::IScoped* function);

    void TranspileExpression(const Structure::Core::Interfaces::IContextNode* context, Services::StringBuilder& stringBuilder);

    void TranspileScope(const Structure::Local::Scope* scope, Services::StringBuilder& stringBuilder, int& maxSlotSize);
}

#endif
