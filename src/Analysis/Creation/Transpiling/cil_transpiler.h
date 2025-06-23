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
    constexpr std::string_view open_flower = "{";
    constexpr std::string_view close_flower = "}";

    constexpr std::string_view pop = "pop";
    constexpr std::string_view dup = "dup";
    constexpr std::string_view ret = "ret";
    constexpr std::string_view load_this = "ldarg.0";

    std::string_view AccessModifierString(const Structure::Core::Interfaces::IDescribable* describable);

    std::string_view StaticModifierString(const Structure::Core::Interfaces::IFunction* describable);
    std::string_view StaticModifierString(const Structure::Core::Interfaces::IUserDefinedType* describable);

    std::string ConstantString(const Structure::Core::Interfaces::ICharacteristic* characteristic);

    std::string ScopedParameterString(const Structure::Core::Interfaces::IScoped* function);
    void ScopedLocalVariableString(const Structure::Core::Interfaces::IScoped* function, Services::StringBuilder& builder);

    std::string ParameterString(const Structure::Core::Interfaces::IParametrized* parametrized);

    void TranspileExpression(const Structure::Core::Interfaces::IContextNode* context, Services::StringBuilder& stringBuilder);

    void TranspileScope(const Structure::Local::Scope* scope, Services::StringBuilder& stringBuilder, int& maxSlotSize);
}

#endif
