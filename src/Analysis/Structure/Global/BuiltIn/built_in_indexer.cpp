#include "built_in_indexer.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BuiltInIndexer::BuiltInIndexer(const IDataType* const creationType, const bool readable, string getInstruction, const bool writable, string setInstruction) : IndexerDefinition(Describer::Public, creationType), readable(readable), writable(writable), getInstruction(std::move(getInstruction)), setInstruction(std::move(setInstruction))
    { }

    MemberType BuiltInIndexer::MemberType() const { return MemberType::BuiltInIndexer; }

    bool BuiltInIndexer::Readable() const { return readable; }
    bool BuiltInIndexer::Writable() const { return writable; }

    bool BuiltInIndexer::PublicGet() const { return readable; }
    bool BuiltInIndexer::PublicSet() const { return writable; }

    const std::string& BuiltInIndexer::SignatureGetString() const { return getInstruction; }
    const std::string& BuiltInIndexer::SignatureSetString() const
    {
        return setInstruction;
    }

    unsigned long BuiltInIndexer::ParameterCount() const { return parameters.size(); }

    const IDataType* BuiltInIndexer::ParameterAt(const unsigned long index) const
    {
        return parameters.at(index);
    }

    void BuiltInIndexer::PushParameterType(const IDataType* type)
    {
        parameters.push_back(type);
    }
}

