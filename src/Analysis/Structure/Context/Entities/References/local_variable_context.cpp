#include "local_variable_context.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    LocalVariableContext::LocalVariableContext(const IVariable* variable, const int index) : IndexedContext(variable, index)
    { }

    MemberType LocalVariableContext::MemberType() const { return MemberType::LocalVariableContext; }

    int LocalVariableContext::SlotCount() const { return creationType->SlotCount(); }
}