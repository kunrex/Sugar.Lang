#ifndef LOCAL_NODE_H
#define LOCAL_NODE_H

#include "../Core/Interfaces/i_node.h"

namespace Analysis::Structure::Local
{
    class LocalNode : public virtual Core::Interfaces::INode
    {
        protected:
            LocalNode();
    };
}

#endif
