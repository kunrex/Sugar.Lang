#include "destructor.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    Destructor::Destructor(const Enums::Describer describer, const DataType* creationType, const ParseNode* body) : DestructorDefinition(describer, creationType), Scoped(body)
    { }

    void Destructor::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::Finalize";
    }
}
