#include "source_directory.h"

#include <iostream>

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure
{
    SourceDirectory::SourceDirectory(const std::string& name, const bool isRoot) : SourceObject(name), Dictionary()
    {
        if (isRoot)
            fullName = name;
    }

    SourceType SourceDirectory::SourceType() const { return SourceType::Directory; }

    bool SourceDirectory::AddChild(const std::string key, SourceObject* const value)
    {
        const auto result = Dictionary::AddChild(key, value);
        if (result)
            value->SetParent(this);

        return result;
    }

    void SourceDirectory::LexParse()
    {
        for (const auto child: values())
            child->LexParse();
    }

    void SourceDirectory::InitDataTypes()
    {
        for (const auto child: values())
            child->InitDataTypes();
    }

    void SourceDirectory::ManageImports()
    {
        for (const auto child: values())
            child->ManageImports();
    }

    void SourceDirectory::BindGlobal()
    {
        for (const auto child: values())
            child->BindGlobal();
    }

    void SourceDirectory::BindLocal()
    {
        for (const auto child: values())
            child->BindLocal();
    }

    void SourceDirectory::Transpile(Services::StringBuilder& builder) const
    {
        for (const auto child: values())
            child->Transpile(builder);
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
