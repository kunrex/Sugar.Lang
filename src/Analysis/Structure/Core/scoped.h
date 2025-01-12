#ifndef SCOPED_H
#define SCOPED_H

#include "../Nodes/Local/scope.h"
#include "../../../Parsing/ParseNodes/parse_node.h"

namespace Analysis::Structure::Core
{
    class Scoped
    {
        protected:
            Local::Scope const scope;
            const ParseNodes::ParseNode* parseNode;

            explicit Scoped(const ParseNodes::ParseNode* parseNode);
    };
}

#endif
