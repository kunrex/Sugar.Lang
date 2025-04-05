#ifndef I_CHARACTERISTIC_H
#define I_CHARACTERISTIC_H

#include "i_variable.h"
#include "../../../Context/context_node.h"

namespace Analysis::Structure::Core::Interfaces
{
    class ICharacteristic : public virtual IVariable
    {
        public:
            [[nodiscard]] virtual const ParseNodes::Core::Interfaces::IParseNode* ParseNode() const = 0;

            virtual void WithContext(const IContextNode* context) const = 0;
            [[nodiscard]] virtual const IContextNode* Context() const = 0;
    };
}

#endif
