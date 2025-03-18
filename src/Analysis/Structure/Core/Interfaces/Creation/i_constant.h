#ifndef I_CONSTANT_H
#define I_CONSTANT_H

#include "i_characteristic.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IConstant : public virtual ICharacteristic
    {
        public:
            virtual void Compile(const std::string& value) = 0;

            virtual void PushDependency(const ICharacteristic* constant) = 0;
            [[nodiscard]] virtual bool IsDependent(const ICharacteristic* constant) const = 0;
    };
}

#endif
