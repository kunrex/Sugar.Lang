#ifndef GLOBAL_NODE_H
#define GLOBAL_NODE_H

#include "../../../Services/child.h"

#include "../Core/Interfaces/i_node.h"
#include "../Core/Interfaces/DataTypes/i_data_type.h"

namespace Analysis::Structure::Global
{
    class GlobalNode : public virtual Core::Interfaces::INode, public Services::ConstantChild<Core::Interfaces::IDataType>
    {
        protected:
            GlobalNode();
    };
}

#endif
