#ifndef I_PROPERTY_H
#define I_PROPERTY_H

#include <string>

namespace Analysis::Structure::Core::Interfaces
{
    class IProperty
    {
        public:
            [[nodiscard]] virtual const std::string& SignatureGetString() const = 0;
            [[nodiscard]] virtual const std::string& SignatureSetString() const = 0;

            virtual ~IProperty() = 0;
    };
}

#endif
