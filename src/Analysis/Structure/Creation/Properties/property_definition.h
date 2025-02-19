#ifndef PROPERTY_DEFINITION_H
#define PROPERTY_DEFINITION_H

#include "../../Core/Interfaces/i_property.h"
#include "../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Creation
{
    class PropertyDefinition : public Core::Characteristic, public Core::Interfaces::IProperty
    {
        protected:
            mutable std::string getSignature;
            mutable std::string setSignature;

            PropertyDefinition(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* parseNode);
    };
}

#endif
