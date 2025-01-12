#include "class.h"

using namespace std;

using namespace ParseNodes::DataTypes;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::DataTypes
{
    Class::Class(const string& name, const Enums::Describer describer) : DataType(name, describer), destructor(nullptr)
    { }

    MemberType Class::MemberType() const { return MemberType::Class; }

    int Class::SlotCount() const { return 1; }

    ClassSource::ClassSource(const string& name, Enums::Describer describer, const DataTypeNode* skeleton) : Class(name, describer), UserDefinedType(skeleton)
    { }

    void Class::PushCharacteristic(Core::Characteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    void Class::PushFunction(Creation::FunctionDefinition* function)
    {
        functions.insert(function);
    }
}


