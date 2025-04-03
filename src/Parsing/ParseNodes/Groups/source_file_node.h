#ifndef SOURCE_FILE_NODE_H
#define SOURCE_FILE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class SourceFileNode final : public DynamicNodeCollection
    {
        public:
            SourceFileNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
