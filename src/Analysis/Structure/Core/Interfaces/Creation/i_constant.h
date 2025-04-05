#ifndef I_CONSTANT_H
#define I_CONSTANT_H

#include "i_characteristic.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IConstant : public virtual ICharacteristic
    {
        public:
            [[nodiscard]] virtual bool Compiled() const = 0;

            virtual void PushDependency(const IConstant* constant) const = 0;
            [[nodiscard]] virtual bool IsDependent(const IConstant* constant) const = 0;
    };
}

#endif
