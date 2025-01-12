#include "source_object.h"

using namespace std;

namespace Analysis::Structure
{
    SourceObject::SourceObject(const string& name) : Child(), Nameable(name)
    { }

    void SourceObject::SetParent(const SourceObject* parent)
    {
        Child::SetParent(parent);
        fullName = parent->FullName() + "." + name;
    }
}
