#include "parameter_context.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ParameterContext::ParameterContext(const IVariable* const variable, const int index) : IndexedContext(variable, index)
    { }

    MemberType ParameterContext::MemberType() const { return MemberType::FunctionParameterContext; }

    int ParameterContext::SlotCount() const { return creationType->SlotCount(); }

    std::string ParameterContext::CILData() const { return std::to_string(index); }
}
