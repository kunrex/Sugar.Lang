#ifndef PROPERTY_H
#define PROPERTY_H

#include "../../Global/global_node.h"
#include "../../../Core/Creation/characteristic.h"

constexpr std::string_view get_property = "__get__Item";
constexpr std::string_view set_property = "__set__Item";

namespace Analysis::Structure::Creation
{
    class Property : public Global::GlobalNode, public Core::Characteristic
    {
        protected:
            Property(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
