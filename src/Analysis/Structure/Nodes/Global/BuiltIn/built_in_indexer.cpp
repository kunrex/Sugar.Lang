#include "built_in_indexer.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInIndexer::BuiltInIndexer(const DataType* creationType, const bool readable, const string& getInstruction, const bool writable, const string& setInstruction) : IndexerDefinition(Describer::Public, creationType), readable(readable), writable(writable)
    {
        getSignature = getInstruction;
        setSignature = setInstruction;
    }

    MemberType BuiltInIndexer::MemberType() const { return MemberType::BuiltInIndexer; }

    bool BuiltInIndexer::Readable() const { return readable; }
    bool BuiltInIndexer::Writable() const { return writable; }

    const std::string& BuiltInIndexer::SignatureGetString() const { return getSignature; }
    const std::string& BuiltInIndexer::SignatureSetString() const { return setSignature; }

    int BuiltInIndexer::ParameterCount() const { return parameterTypes.size();}
    const DataType* BuiltInIndexer::ParameterAt(const int index) const
    {
        if (index >= 0 && index < parameterTypes.size())
            return parameterTypes.at(index);

        return nullptr;
    }
}

