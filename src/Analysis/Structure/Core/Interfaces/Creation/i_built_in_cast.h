#ifndef I_BUILT_IN_CAST_H
#define I_BUILT_IN_CAST_H

#include "i_function.h"

#include "i_built_in_overload.h"

namespace Analysis::Structure::Core::Interfaces
{
    typedef Compilation::CompilationResult (*CastFunction) (const Compilation::CompilationResult& argument);

    class IBuiltInCast : public virtual IFunction
    {
        public:
            [[nodiscard]] virtual Compilation::CompilationResult StaticCompile(const Compilation::CompilationResult& argument) const = 0;
    };
}

#endif
