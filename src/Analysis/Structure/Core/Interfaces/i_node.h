#ifndef I_NODE_H
#define I_NODE_H

#include "../../Enums/member_type.h"

namespace Analysis::Structure::Core::Interfaces
{
    class INode
    {
        public:
            [[nodiscard]] virtual Enums::MemberType MemberType() const = 0;

            virtual ~INode();
    };
}

#endif
