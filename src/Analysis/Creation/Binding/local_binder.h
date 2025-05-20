#ifndef LOCAL_BINDER_H
#define LOCAL_BINDER_H

#include "../../Structure/Core/Interfaces/Scoped/i_scoped.h"

namespace Analysis::Creation::Binding
{
    void BindScoped(const Structure::Core::Interfaces::IScoped* scoped);
}

#endif
