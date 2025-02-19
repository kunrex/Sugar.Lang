#include "parse_node.h"

#include "Conditions/condition_node.h"
#include "Statements/declaration_node.h"

using namespace std;

using namespace Services;

using namespace ParseNodes::Conditions;
using namespace ParseNodes::Statements;

namespace ParseNodes
{
    ParseNode::ParseNode() : IParseNode()
    { }

    bool ParseNode::DefinesChildren() const { return false; }

    void ParseNode::Print(string indent, const bool last) const
    {
        cout << indent;
        if (last)
        {
            cout << "\\-";
            indent += "  ";
        }
        else
        {
            cout << "|-";
            indent += "| ";
        }

        cout << endl;
        PrintChildren(indent);
    }

    void ParseNode::PrintChildren(const string indent) const
    { }

    template <class TChild>
    NodeCollection<TChild>::NodeCollection() : ParseNode(), Services::ConstantCollection<TChild>()
    { }

    template <class TChild>
    void NodeCollection<TChild>::PrintChildren(const string indent) const
    {
        unsigned long i = 0;
        const auto length = this->children.size();

        for (const auto child : this->children)
            child->Print(indent, ++i == length);
    }

    template <class TChild>
    bool NodeCollection<TChild>::DefinesChildren() const { return true; }

    template class NodeCollection<ParseNode>;
    template class NodeCollection<ConditionNode>;
    template class NodeCollection<DeclarationNode>;
}
