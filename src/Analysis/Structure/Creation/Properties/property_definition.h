#ifndef PROPERTY_DEFINITION_H
#define PROPERTY_DEFINITION_H

#include "../../Core/Creation/characteristic.h"
#include "../../Core/Creation/property_signature.h"

namespace Analysis::Structure::Creation
{
    class PropertyDefinition : public Core::Characteristic, public Core::PropertySignature
    {
        protected:
            PropertyDefinition(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* parseNode);
    };
}

#endif
