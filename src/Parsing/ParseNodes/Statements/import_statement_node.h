#ifndef IMPORT_STATEMENT_NODE_H
#define IMPORT_STATEMENT_NODE_H

#include "statement_node.h"

namespace ParseNodes::Statements
{
    class ImportStatementNode final : public StatementNode
    {
        private:
            const Tokens::Token& path;
            const Tokens::Token& keyword;

        public:
            ImportStatementNode(const Tokens::Token& path, const Tokens::Token& keyword, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] std::string Path() const;
    };
}

#endif
