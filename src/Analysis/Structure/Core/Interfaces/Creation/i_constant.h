#ifndef I_CONSTANT_H
#define I_CONSTANT_H

#include "i_characteristic.h"
#include "../../../Compilation/compilation_result.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IConstant : public virtual ICharacteristic
    {
        public:
            virtual void PushDependency(const IConstant* constant) const = 0;
            [[nodiscard]] virtual bool IsDependent(const IConstant* constant) const = 0;

            virtual void Compile(Compilation::CompilationResult result) const = 0;
            [[nodiscard]] virtual Compilation::CompilationResult AsCompilationResult() const = 0;
    };
}

#endif
