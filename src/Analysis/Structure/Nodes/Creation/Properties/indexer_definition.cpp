#include "indexer_definition.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    IndexerDefinition::IndexerDefinition(const Enums::Describer describer, const DataType* creationType) : Function(describer, creationType)
    { }

    std::string IndexerDefinition::SignatureStringSet() const
    {
        auto base = SignatureString();
        return base.insert(base.size() - 2, " " + creationType->FullName());
    }
}
