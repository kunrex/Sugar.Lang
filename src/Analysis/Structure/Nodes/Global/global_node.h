#ifndef GLOBAL_NODE_H
#define GLOBAL_NODE_H

#include "../../source_object.h"
#include "../../../../Services/child.h"
#include "../../Core/Interfaces/i_node.h"

namespace Analysis::Structure::Global
{
    class GlobalNode : public Core::Interfaces::INode, public Services::Child<Core::DataType>
    {
        protected:
            GlobalNode();
    };
}

#endif
