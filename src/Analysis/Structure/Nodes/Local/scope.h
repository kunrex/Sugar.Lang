#ifndef SCOPE_H
#define SCOPE_H

#include "local_node.h"

namespace Analysis::Structure::Local
{
    class Scope final : public LocalNode
    {
        public:
            [[nodiscard]] Enums::MemberType MemberType() const override;
    };
}

#endif
