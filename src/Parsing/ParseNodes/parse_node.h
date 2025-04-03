#ifndef PARSE_NODE_H
#define PARSE_NODE_H

#include <array>
#include <vector>

#include "Core/Interfaces/i_parse_node.h"

#include "../../Lexing/Tokens/token.h"
#include "Enums/child_code.h"

namespace ParseNodes
{
    class ParseNode : public virtual Core::Interfaces::IParseNode
    {
        protected:
            const Tokens::Token& token;

            explicit ParseNode(const Tokens::Token& token);

        public:
            [[nodiscard]] const Tokens::Token& Token() const override;

            [[nodiscard]] int ChildCount() const override;
            [[nodiscard]] const IParseNode* GetChild(int index) const override;
    };

    template <int childCount>
    class FixedNodeCollection : public ParseNode
    {
        protected:
            std::array<std::tuple<int, const IParseNode*>, childCount> children;

            void AddChild(Enums::ChildCode code, const IParseNode* child);

            explicit FixedNodeCollection(const Tokens::Token& token);

        public:
            [[nodiscard]] int ChildCount() const override;
            [[nodiscard]] const IParseNode* GetChild(int index) const override;
    };

    class DynamicNodeCollection : public ParseNode
    {
        protected:
            std::vector<const IParseNode*> children;

            explicit DynamicNodeCollection(const Tokens::Token& token);

        public:
            [[nodiscard]] int ChildCount() const override;
            [[nodiscard]] const IParseNode* GetChild(int index) const override;

            void AddChild(const IParseNode* child);
    };
}

#endif
