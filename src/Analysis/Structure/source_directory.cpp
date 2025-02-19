#include "source_directory.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure
{
    SourceDirectory::SourceDirectory(const string& name) : SourceObject(name), Dictionary()
    { }

    SourceType SourceDirectory::SourceType() const { return SourceType::Directory; }

    bool SourceDirectory::AddChild(const string key, SourceObject* const value)
    {
        const auto result = Dictionary::AddChild(key, value);
        if (result)
            value->SetParent(this);

        return result;
    }
}
