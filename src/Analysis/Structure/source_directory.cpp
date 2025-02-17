#include "source_directory.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure
{
    SourceDirectory::SourceDirectory(const string& name) : SourceObject(name), Dictionary()
    { }

    SourceType SourceDirectory::SourceType() const { return SourceType::Directory; }

    bool SourceDirectory::Push(const string key, SourceObject* const value)
    {
        const auto result = Dictionary::Push(key, value);
        if (result)
            value->SetParent(this);

        return result;
    }

    void SourceDirectory::ReferenceThis(SourceObject* other)
    {
        for (auto const& child: map)
            if (child.second->SourceType() == SourceType::File)
                child.second->ReferenceThis(other);
    }

    void SourceDirectory::AddReference(const DataType* dataType)
    { }
}
