#ifndef INODE_H
#define INODE_H

#include "../../Enums/node_type.h"
#include "../../../../Services/child.h"
#include "../../../../Services/printable.h"

namespace ParseNodes::Core::Interfaces
{
    template <class TDefault>
    class IParseNode : public Services::Printable, public Services::Child<TDefault>
    {
        public:
            [[nodiscard]] virtual Enums::NodeType NodeType() const = 0;

            [[nodiscard]] virtual bool DefinesChildren() const = 0;
    };
}

#endif //INODE_H
