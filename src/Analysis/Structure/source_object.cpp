#include "source_object.h"

namespace Analysis::Structure
{
    SourceObject::SourceObject(const std::string& name) : Nameable(name), Child()
    { }

    const std::string& SourceObject::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }
}
