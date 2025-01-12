#include "constructor.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    Constructor::Constructor(const Enums::Describer describer, const DataType* creationType, const ParseNode* body) : ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    void Constructor::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::.ctor";
    }
}

