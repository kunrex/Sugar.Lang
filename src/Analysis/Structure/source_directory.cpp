#include "source_directory.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure
{
    SourceDirectory::SourceDirectory(const string& name) : SourceObject(name), Collection()
    { }

    SourceType SourceDirectory::SourceType() const { return SourceType::Directory; }

    void SourceDirectory::AddChild(SourceObject* const child)
    {
        Collection::AddChild(child);
        child->SetParent(this);
    }

    void SourceDirectory::ReferenceThis(SourceObject* other)
    {
        for (auto const child: children)
            if (child->SourceType() == SourceType::File)
                child->ReferenceThis(other);
    }

    void SourceDirectory::AddReference(const DataType* dataType)
    { }
}
