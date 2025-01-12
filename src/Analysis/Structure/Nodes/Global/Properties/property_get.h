#ifndef PROPERTY_GET_H
#define PROPERTY_GET_H

#include "../../../Core/Creation/getable.h"
#include "../../Creation/Properties/property.h"

namespace Analysis::Structure::Global
{
    class PropertyGet final : public Creation::Property, public Core::Getable
    {
        public:
            PropertyGet(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, Creation::Get* get);
    };
}

#endif
