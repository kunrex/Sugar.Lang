#include "indexer.h"

#include <format>

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Global
{
    Indexer::Indexer(const Enums::Describer describer, const DataType* creationType, const MethodDefinition* get, const VoidDefinition* set) : IndexerDefinition(describer, creationType), get(get), set(set), readable(false), getInstruction(), writable(false), setInstruction()
    {
        if (get != nullptr)
        {
            readable = true;
            getInstruction = std::format("call {}", get->SignatureString());
        }

        if (set != nullptr)
        {
            writable = true;
            setInstruction = std::format("call {}", set->SignatureString());
        }
    }

    MemberType Indexer::MemberType() const { return MemberType::Indexer; }

    bool Indexer::Readable() const { return readable; }
    bool Indexer::Writable() const { return writable; }

    const std::string& Indexer::SignatureGetString() const { return getInstruction; }
    const std::string& Indexer::SignatureSetString() const { return setInstruction; }

    unsigned long Indexer::ParameterCount() const { return get == nullptr ? set->ParameterCount() - 1 : get->ParameterCount(); }
    const DataType* Indexer::ParameterAt(const unsigned long index) const { return get == nullptr ? set->ParameterAt(index) : get->ParameterAt(index); }
}
