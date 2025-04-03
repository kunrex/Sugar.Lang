#ifndef IMPORT_STATEMENT_NODE_H
#define IMPORT_STATEMENT_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class ImportStatementNode final : public ParseNode
    {
        public:
            explicit ImportStatementNode(const Tokens::Token& path);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
