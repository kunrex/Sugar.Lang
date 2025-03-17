#include "local_variable.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Local
{
    LocalVariable::LocalVariable(const string& name, const Enums::Describer describer, const IDataType* const creationType) : Variable(name, describer, creationType)
    { }

    MemberType LocalVariable::MemberType() const { return MemberType::LocalVariable; }

    const std::string& LocalVariable::FullName() const { return name; }

    bool LocalVariable::Readable() const { return true; }
    bool LocalVariable::Writable() const { return !CheckDescriber(Describer::Const); }
}
