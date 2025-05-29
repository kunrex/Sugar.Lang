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

    const std::string& BuiltInConstant::FullName() const { return fullName; }

    void BuiltInConstant::BindLocal()
    { }

    void BuiltInConstant::Transpile(Services::StringBuilder& builder) const
    { }

    void BuiltInConstant::IncrementDependencyCount()
    { }

    void BuiltInConstant::PushDependant(ICharacteristic* const characteristic) const
    { }

    bool BuiltInConstant::HasDependant(const ICharacteristic* characteristic) const { return false; }
}