#ifndef I_PROPERTY_SIGNATURE_H
#define I_PROPERTY_SIGNATURE_H

#include <string>

#include "../i_read_write.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IPropertySignature : public virtual IReadWrite
    {
        public:
            [[nodiscard]] virtual bool PublicGet() const = 0;
            [[nodiscard]] virtual bool PublicSet() const = 0;

            [[nodiscard]] virtual const std::string& SignatureGetString() const = 0;
            [[nodiscard]] virtual const std::string& SignatureSetString() const = 0;
    };
}

#endif
