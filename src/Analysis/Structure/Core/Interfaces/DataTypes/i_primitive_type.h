#ifndef I_PRIMITIVE_TYPE_H
#define I_PRIMITIVE_TYPE_H

#include "i_data_type.h"

#include "../Creation/i_built_in_overload.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IBuiltInCast;
    class IBuiltInOverload;

    class IPrimitiveType : public virtual IDataType
    {
        public:
            [[nodiscard]] virtual const IBuiltInCast* FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const = 0;

            [[nodiscard]] virtual const IBuiltInOverload* FindBuiltInOverload(Tokens::Enums::SyntaxKind base) const = 0;
    };
}

#endif
