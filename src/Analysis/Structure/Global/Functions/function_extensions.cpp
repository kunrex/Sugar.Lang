#include "function_extensions.h"

using namespace std;

namespace Analysis::Structure::Global
{
    std::string ParameterString(const Core::Interfaces::IParametrized* const parametrized)
    {
        string value;
        const auto count = parametrized->ParameterCount();

        for (int i = 0; i < count; i++)
        {
            value += parametrized->ParameterAt(i)->FullName();
            if (i < count - 1)
                value += " ";
        }

        return value + ")";
    }
}
