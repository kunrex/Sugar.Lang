#include "source_file.h"

#include "Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure
{
    SourceFile::SourceFile(const string& name, string source) : SourceObject(name), Dictionary(), source(std::move(source)), tokens(), sourceNode(nullptr), references()
    { }

    SourceType SourceFile::SourceType() const { return SourceType::File; }

    bool SourceFile::AddChild(const string key, DataType* const value)
    {
        const auto result = Dictionary::AddChild(key, value);
        if (result)
            value->SetParent(this);

        return result;
    }

    void SourceFile::AddReference(const Interfaces::IDataType* const dataType)
    {
        references[dataType->Name()] == dataType;
    }

    const Interfaces::IDataType* SourceFile::GetReference(const string& name) const
    {
        return references.contains(name) ? nullptr : references.at(name);
    }

    unsigned long SourceFile::SourceLength() const { return source.size(); }
    char SourceFile::SourceAt(const unsigned long i) const { return source.at(i); }

    void SourceFile::PushBackToken(Tokens::Token token)
    {
        tokens.push_back(std::move(token));
    }

    unsigned long SourceFile::TokenCount() const { return tokens.size(); }
    const Tokens::Token& SourceFile::TokenAt(const unsigned long i) { return tokens.at(i); }

    void SourceFile::WithSourceNode(SourceFileNode* const source)
    {
        if (sourceNode != nullptr)
            sourceNode = source;
    }
    const SourceFileNode* SourceFile::SourceNode() const { return sourceNode; }

    SourceFile::~SourceFile()
    {
        delete sourceNode;
    }
}
