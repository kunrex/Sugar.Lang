#include "indexer.h"

using namespace Services;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    IndexerDefinition::IndexerDefinition(const Enums::Describer describer, const IDataType* const creationType) : Describable(describer), Created(creationType)
    { }

    Indexer::Indexer(const Enums::Describer describer, const IDataType* const creationType, const unsigned long parameterCount) : IndexerDefinition(describer, creationType), parameterCount(parameterCount)
    { }

    MemberType Indexer::MemberType() const { return MemberType::Indexer; }

    unsigned long Indexer::ParameterCount() const { return parameterCount; }

    GetIndexer::GetIndexer(const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get) : Indexer(describer, creationType, get->ParameterCount()), get(get)
    { }

    bool GetIndexer::Readable() const { return true; }
    bool GetIndexer::Writable() const { return false; }

    bool GetIndexer::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool GetIndexer::PublicSet() const { return false; }

    const std::string& GetIndexer::SignatureGetString() const { return get->FullName(); }
    const std::string& GetIndexer::SignatureSetString() const { return get->FullName(); }

    const IDataType* GetIndexer::ParameterAt(const unsigned long index) const { return get->ParameterAt(index); }

    SetIndexer::SetIndexer(const Enums::Describer describer, const IDataType* const creationType, const IFunction* const set) : Indexer(describer, creationType, set->ParameterCount() - 1), set(set)
    { }

    bool SetIndexer::Readable() const { return false; }
    bool SetIndexer::Writable() const { return true; }

    bool SetIndexer::PublicGet() const { return false; }
    bool SetIndexer::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& SetIndexer::SignatureGetString() const { return set->FullName(); }
    const std::string& SetIndexer::SignatureSetString() const { return set->FullName(); }

    const IDataType* SetIndexer::ParameterAt(const unsigned long index) const { return set->ParameterAt(index); }

    GetSetIndexer::GetSetIndexer(const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get, const IFunction* const set) : Indexer(describer, creationType, get->ParameterCount()), get(get), set(set)
    { }

    bool GetSetIndexer::Readable() const { return true; }
    bool GetSetIndexer::Writable() const { return true; }

    bool GetSetIndexer::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool GetSetIndexer::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& GetSetIndexer::SignatureGetString() const { return get->FullName(); }
    const std::string& GetSetIndexer::SignatureSetString() const { return set->FullName(); }

    const IDataType* GetSetIndexer::ParameterAt(const unsigned long index) const { return get->ParameterAt(index); }

    BuiltInIndexer::BuiltInIndexer(const IDataType* const creationType, const bool readable, std::string getInstruction, const bool writable, std::string setInstruction) : IndexerDefinition(Describer::Public, creationType), readable(readable), writable(writable), getInstruction(std::move(getInstruction)), setInstruction(std::move(setInstruction))
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
