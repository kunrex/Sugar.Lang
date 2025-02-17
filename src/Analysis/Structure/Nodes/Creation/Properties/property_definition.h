#ifndef PROPERTY_DEFINITION_H
#define PROPERTY_DEFINITION_H

#include "../../Global/global_node.h"
#include "../../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Creation
{
    class PropertyDefinition : public Global::GlobalNode, public Core::Characteristic
    {
        protected:
            mutable std::string getSignature;
            mutable std::string setSignature;

        PropertyDefinition(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);

        public:
            [[nodiscard]] virtual const std::string& SignatureGetString() const = 0;
            [[nodiscard]] virtual const std::string& SignatureSetString() const = 0;
    };
}

#endif
