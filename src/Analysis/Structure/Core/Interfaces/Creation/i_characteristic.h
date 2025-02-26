#ifndef I_CHARACTERISTIC_H
#define I_CHARACTERISTIC_H

#include "i_variable.h"

namespace Analysis::Structure::Core::Interfaces
{
    class ICharacteristic : public virtual IVariable
    {
        public:
            [[nodiscard]] virtual const ParseNodes::ParseNode* ParseNode() const = 0;
    };
}

#endif
