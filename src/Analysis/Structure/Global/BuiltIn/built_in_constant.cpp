#include "built_in_constant.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BuiltInConstant::BuiltInConstant(const std::string& name, const Enums::Describer describer, const IDataType* creationType, const IContextNode* const context) : Characteristic(name, describer, creationType, nullptr)
    {
        this->context = context;
    }

    MemberType BuiltInConstant::MemberType() const { return MemberType::ConstantField; }

    bool BuiltInConstant::Readable() const { return true; }
    bool BuiltInConstant::Writable() const { return false; }

    bool BuiltInConstant::Compiled() const { return true; }

    const std::string& BuiltInConstant::FullName() const { return fullName; }

    bool BuiltInConstant::IsDependent(const IConstant* constant) const { return false; }
    void BuiltInConstant::PushDependency(const IConstant* constant) const
    { }

    void BuiltInConstant::BindLocal()
    { }
}