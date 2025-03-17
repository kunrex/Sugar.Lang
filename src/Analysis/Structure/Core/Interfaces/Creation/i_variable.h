#ifndef I_VARIABLE_H
#define I_VARIABLE_H

#include "../i_created.h"
#include "../i_nameable.h"
#include "../i_read_write.h"
#include "../i_describable.h"
#include "../i_fully_nameable.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IVariable : public virtual INode, public virtual INameable, public virtual IFullyNameable, public virtual IDescribable, public virtual ICreated, public virtual IReadWrite
    {

    };
}

#endif
