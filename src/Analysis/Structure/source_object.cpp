#include "source_object.h"

using namespace std;

namespace Analysis::Structure
{
    SourceObject::SourceObject(const string& name) : Child(), Nameable(name)
    { }

    const std::string& SourceObject::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "." + name;

        return fullName;
    }
}
