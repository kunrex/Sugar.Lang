#ifndef FUNCTION_EXTENSIONS_H
#define FUNCTION_EXTENSIONS_H

#include <string>

#include "../../Core/Interfaces/i_parametrized.h"

namespace Analysis::Structure::Global
{
    [[nodiscard]] std::string ParameterString(const Core::Interfaces::IParametrized* parametrized);
}

#endif
