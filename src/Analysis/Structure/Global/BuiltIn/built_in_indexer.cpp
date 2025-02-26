#include "built_in_indexer.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInIndexer::BuiltInIndexer(const Interfaces::IDataType* creationType, const bool readable, const string& getInstruction, const bool writable, const string& setInstruction) : IndexerDefinition(Describer::Public, creationType), BuiltInFunction(), readable(readable), writable(writable)
    {
        this->getInstruction = getInstruction;
        this->setInstruction = setInstruction;
    }

    const std::string& BuiltInIndexer::FullName() const { return creationType->Name(); }

    MemberType BuiltInIndexer::MemberType() const { return MemberType::BuiltInIndexer; }

    bool BuiltInIndexer::Readable() const { return readable; }
    bool BuiltInIndexer::Writable() const { return writable; }

    const std::string& BuiltInIndexer::SignatureGetString() const { return getInstruction; }
    const std::string& BuiltInIndexer::SignatureSetString() const { return setInstruction; }
}

