#include "source_directory.h"

#include <iostream>
#include <ostream>

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

    void SourceDirectory::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Sugar Directory: " << name << std::endl;
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        const auto childCount = map.size();
        for (const auto& child: map)
            child.second->Print(next, ++i == childCount);
    }

}
