#ifndef PROPERTY_DEFINITION_H
#define PROPERTY_DEFINITION_H

#include "../../Core/property_signature.h"
#include "../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Creation
{
    class PropertyDefinition : public Core::Characteristic, public Core::PropertySignature
    {
        protected:
            PropertyDefinition(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* parseNode);
    };
}

#endif
