#include "indexer.h"

#include <format>

using namespace Services;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    Indexer::Indexer(const Enums::Describer describer, const IDataType* const creationType, const unsigned long parameterCount) : IndexerDefinition(describer, creationType), parameterCount(parameterCount)
    { }

    MemberType Indexer::MemberType() const { return MemberType::Indexer; }

    unsigned long Indexer::ParameterCount() const { return parameterCount; }

    GetIndexer::GetIndexer(const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get) : Indexer(describer, creationType, get->ParameterCount()), getInstruction("call " + get->FullName()), get(get)
    { }

    bool GetIndexer::Readable() const { return true; }
    bool GetIndexer::Writable() const { return false; }

    bool GetIndexer::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool GetIndexer::PublicSet() const { return false; }

    const std::string& GetIndexer::SignatureGetString() const { return getInstruction; }
    const std::string& GetIndexer::SignatureSetString() const { return getInstruction; }

    const IDataType* GetIndexer::ParameterAt(const unsigned long index) const { return get->ParameterAt(index); }

    SetIndexer::SetIndexer(const Enums::Describer describer, const IDataType* const creationType, const IFunction* const set) : Indexer(describer, creationType, set->ParameterCount() - 1), setInstruction("call " + set->FullName()), set(set)
    { }

    bool SetIndexer::Readable() const { return false; }
    bool SetIndexer::Writable() const { return true; }

    bool SetIndexer::PublicGet() const { return false; }
    bool SetIndexer::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& SetIndexer::SignatureGetString() const { return setInstruction; }
    const std::string& SetIndexer::SignatureSetString() const { return setInstruction; }

    const IDataType* SetIndexer::ParameterAt(const unsigned long index) const { return set->ParameterAt(index); }

    GetSetIndexer::GetSetIndexer(const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get, const IFunction* const set) : Indexer(describer, creationType, get->ParameterCount()), getInstruction("call " + get->FullName()), get(get), setInstruction("call " + set->FullName()), set(set)
    { }

    bool GetSetIndexer::Readable() const { return true; }
    bool GetSetIndexer::Writable() const { return true; }

    bool GetSetIndexer::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool GetSetIndexer::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& GetSetIndexer::SignatureGetString() const { return getInstruction; }
    const std::string& GetSetIndexer::SignatureSetString() const { return setInstruction; }

    const IDataType* GetSetIndexer::ParameterAt(const unsigned long index) const { return get->ParameterAt(index); }
}
