#include "explicit_cast.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    ExplicitCast::ExplicitCast(const Enums::Describer describer, const DataType* creationType, const ParseNode* body) : CastDefinition(describer, creationType), Scoped(body)
    { }

    void ExplicitCast::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::__explicit__" + creationType->FullName();
    }

    bool ExplicitCast::operator<(const ExplicitCast& rhs) const
    {
        if (fullName != rhs.fullName)
            return fullName < rhs.fullName;

        return Function::operator<(rhs);
    }
}
