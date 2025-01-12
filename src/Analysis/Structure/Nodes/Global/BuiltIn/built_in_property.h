#ifndef BUILT_IN_PROPERTY_H
#define BUILT_IN_PROPERTY_H

#include "../../Creation/Properties/property.h"

namespace Analysis::Structure::Global
{
    class BuiltInProperty final : public Creation::Property
    {
        protected:
            const std::string getInstruction;
            const std::string setInstruction;

        public:
            BuiltInProperty(Enums::Describer describer, const std::string& name, const Core::DataType* creationType, std::string getInstruction, std::string setInstruction);

            [[nodiscard]] std::string GetInstruction() const;
            [[nodiscard]] std::string SetInstruction() const;
    };
}

#endif
