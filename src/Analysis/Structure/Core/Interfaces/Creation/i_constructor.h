#ifndef I_CONSTRUCTOR_H
#define I_CONSTRUCTOR_H

#include "i_function.h"
#include "i_characteristic.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IConstructor : public virtual IFunction, public virtual ITranspilable, public virtual ILocallyBindable
    {
        public:
            virtual void PushTranspilation(const ICharacteristic* characteristic) = 0;
            virtual void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const = 0;
    };
}

#endif
