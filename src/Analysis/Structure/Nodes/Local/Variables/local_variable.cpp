#include "local_variable.h"

#include <utility>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Local
{
    LocalVariable::LocalVariable(const string& name, const Enums::Describer describer, const DataType* creationType) : Variable(name, describer, creationType)
    {
        fullName = name;
    }

    MemberType LocalVariable::MemberType() const { return MemberType::LocalVariable; }

    const std::string& LocalVariable::FullName() const { return fullName; }
}
