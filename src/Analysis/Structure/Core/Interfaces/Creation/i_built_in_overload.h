#ifndef I_BUILT_IN_OVERLOAD_H
#define I_BUILT_IN_OVERLOAD_H

#include "i_operator_overload.h"

namespace Analysis::Structure::Compilation
{
    struct CompilationResult;
}

namespace Analysis::Structure::Core::Interfaces
{
    typedef Compilation::CompilationResult (*OverloadFunction) (const std::vector<Compilation::CompilationResult>& arguments);

    class IBuiltInOverload : public virtual IOperatorOverload
    {
        public:
            [[nodiscard]] virtual Compilation::CompilationResult StaticCompile(const std::vector<Compilation::CompilationResult>& arguments) const = 0;
    };
}

#endif
