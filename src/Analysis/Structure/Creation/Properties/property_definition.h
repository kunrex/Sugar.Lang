#ifndef PROPERTY_DEFINITION_H
#define PROPERTY_DEFINITION_H

#include "../../Core/Creation/characteristic.h"
#include "../../Core/Interfaces/Creation/i_property_signature.h"

namespace Analysis::Structure::Creation
{
    class PropertyDefinition : public Core::Characteristic, public virtual Core::Interfaces::IPropertySignature
    {
        protected:
            PropertyDefinition(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* parseNode);
    };
}

#endif
