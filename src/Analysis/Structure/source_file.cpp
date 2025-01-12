#include "source_file.h"

#include "Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure
{
    SourceFile::SourceFile(const string& name, string source) : SourceObject(name), Collection(),  source(std::move(source)), references(), sourceNode(nullptr)
    { }

    SourceType SourceFile::SourceType() const { return SourceType::File; }

    void SourceFile::AddChild(DataType* const child)
    {
        BaseCollection::AddChild(child);
        child->SetParent(this);
    }

    void SourceFile::ReferenceThis(SourceObject* other)
    {
        for (const auto child: references)
            other->AddReference(child);
    }

    void SourceFile::AddReference(const DataType* dataType)
    {
        references.push_back(dataType);
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
