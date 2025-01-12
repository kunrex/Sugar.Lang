#ifndef PROPERTY_GET_SET_H
#define PROPERTY_GET_SET_H

#include "../../../Core/Creation/get_set.h"
#include "../../Creation/Properties/property.h"

namespace Analysis::Structure::Global
{
    class PropertyGetSet final : public Creation::Property, public Core::GetSet
    {
        public:
            PropertyGetSet(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, Creation::Get* get, Creation::Set* set);
    };
}

#endif
