#ifndef I_CHARACTERISTIC_H
#define I_CHARACTERISTIC_H

#include "i_variable.h"

#include "../i_bindable.h"
#include "../i_transpilable.h"

#include "../../../Context/context_node.h"

namespace Analysis::Structure::Core::Interfaces
{
    class ICharacteristic : public virtual IVariable, public virtual ILocallyBindable, public virtual ITranspilable
    {
        public:
            [[nodiscard]] virtual const ParseNodes::Core::Interfaces::IParseNode* ParseNode() const = 0;

            [[nodiscard]] virtual const IContextNode* Context() const = 0;

            virtual void IncrementDependencyCount() = 0;
            virtual void PushDependant(ICharacteristic* characteristic) const = 0;
            [[nodiscard]] virtual bool HasDependant(const ICharacteristic* characteristic) const = 0;
    };
}

#endif
