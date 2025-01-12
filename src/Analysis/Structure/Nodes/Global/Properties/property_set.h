#ifndef PROPERTY_SET_H
#define PROPERTY_SET_H

#include "../../../Core/Creation/setable.h"
#include "../../Creation/Properties/property.h"

namespace Analysis::Structure::Global
{
    class PropertySet final : public Creation::Property, public Core::Setable
    {
        public:
            PropertySet(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, Creation::Set* set);
    };
}

#endif
