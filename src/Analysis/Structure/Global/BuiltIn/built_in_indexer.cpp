#include "built_in_indexer.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInIndexer::BuiltInIndexer(const DataType* creationType, const bool readable, const string& getInstruction, const bool writable, const string& setInstruction) : IndexerDefinition(Describer::Public, creationType), readable(readable), writable(writable), parameters()
    {
        this->getInstruction = getInstruction;
        this->setInstruction = setInstruction;
    }

    MemberType BuiltInIndexer::MemberType() const { return MemberType::BuiltInIndexer; }

    bool BuiltInIndexer::Readable() const { return readable; }
    bool BuiltInIndexer::Writable() const { return writable; }

    const std::string& BuiltInIndexer::SignatureGetString() const { return getInstruction; }
    const std::string& BuiltInIndexer::SignatureSetString() const { return setInstruction; }

    unsigned long BuiltInIndexer::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInIndexer::ParameterAt(const unsigned long index) const { return parameters.at(index); }

    void BuiltInIndexer::PushParameterType(const DataType* type)
    {
        parameters.push_back(type);
    }
}

