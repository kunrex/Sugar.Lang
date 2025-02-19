#ifndef GLOBAL_NODE_H
#define GLOBAL_NODE_H

#include "../../../Services/child.h"

#include "../source_object.h"
#include "../Core/Interfaces/i_node.h"

namespace Analysis::Structure::Global
{
    class GlobalNode : public virtual Core::Interfaces::INode, public Services::ConstantChild<Core::DataType>
    {
        protected:
            GlobalNode();
    };
}

#endif
