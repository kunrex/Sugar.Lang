#ifndef SOURCE_FILE_NODE_H
#define SOURCE_FILE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class SourceFileNode final : public NodeCollection<ParseNode>
    {
        public:
            SourceFileNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
