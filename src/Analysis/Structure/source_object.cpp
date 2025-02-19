#include "source_object.h"

using namespace std;

namespace Analysis::Structure
{
    SourceObject::SourceObject(const string& name) : Nameable(name), Child()
    { }

    const std::string& SourceObject::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }
}
