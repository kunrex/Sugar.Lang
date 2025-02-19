#ifndef DEFAULT_VALUED_H
#define DEFAULT_VALUED_H

#include "../../../Parsing/ParseNodes/parse_node.h"

namespace Analysis::Structure::Core
{
    class DefaultValued
    {
        protected:
            const ParseNodes::ParseNode* parseNode;

        public:
            explicit DefaultValued(const ParseNodes::ParseNode* parseNode);

            [[nodiscard]] const ParseNodes::ParseNode* ParseNode() const;
    };
}

#endif
