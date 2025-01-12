#ifndef RETURN_NODE_H
#define RETURN_NODE_H

#include "../statement_node.h"

namespace ParseNodes::Statements
{
    class ReturnNode final : public StatementNode
    {
        private:
            const ParseNode* value;

        public:
            explicit ReturnNode(const Tokens::Token& separator);
            ReturnNode(const ParseNode* value, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Value() const;

            ~ReturnNode() override;
    };
}

#endif //RETURN_NODE_H
