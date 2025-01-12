#ifndef PARSE_NODE_H
#define PARSE_NODE_H

#include "../../Services/collection.h"
#include "Core/Interfaces/i_parse_node.h"

namespace ParseNodes
{
    class ParseNode : public Core::Interfaces::IParseNode<ParseNode>
    {
        protected:
            ParseNode();

            virtual void PrintChildren(std::string indent) const;

        public:
            void Print(std::string indent, bool last) const override;

            [[nodiscard]] bool DefinesChildren() const override;
    };

    template <class TChild>
    class NodeCollection : public ParseNode, public Services::ConstantCollection<TChild>
    {
        protected:
            NodeCollection();

            void PrintChildren(std::string indent) const override;

        public:
            [[nodiscard]] bool DefinesChildren() const override;
    };
}

#endif
