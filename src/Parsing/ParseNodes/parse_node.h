#ifndef PARSE_NODE_H
#define PARSE_NODE_H

#include <array>
#include <vector>

#include "Enums/child_code.h"

#include "Core/Interfaces/i_parse_node.h"

#include "../../Lexing/Tokens/token.h"

namespace ParseNodes
{
    class ParseNode : public virtual Core::Interfaces::IParseNode
    {
        protected:
            const Tokens::Token& token;

            explicit ParseNode(const Tokens::Token& token);

        public:
            [[nodiscard]] const Tokens::Token& Token() const override;

            [[nodiscard]] unsigned long ChildCount() const override;
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
            [[nodiscard]] unsigned long ChildCount() const override;
            [[nodiscard]] const IParseNode* GetChild(int index) const override;

            ~FixedNodeCollection() override;
    };

    class DynamicNodeCollection : public ParseNode
    {
        protected:
            std::vector<const IParseNode*> children;

            explicit DynamicNodeCollection(const Tokens::Token& token);

        public:
            [[nodiscard]] unsigned long ChildCount() const override;
            [[nodiscard]] const IParseNode* GetChild(int index) const override;

            void AddChild(const IParseNode* child);

            ~DynamicNodeCollection() override;
    };
}

#endif
