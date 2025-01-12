#include "implicit_cast.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    ImplicitCast::ImplicitCast(const Enums::Describer describer, const DataType* creationType, const ParseNode* body) : CastDefinition(describer, creationType), Scoped(body)
    { }

    void ImplicitCast::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::__implicit__" + creationType->FullName();
    }

    bool ImplicitCast::operator<(const ImplicitCast& rhs) const
    {
        if (fullName != rhs.fullName)
            return fullName < rhs.fullName;

        return Function::operator<(rhs);
    }
}
