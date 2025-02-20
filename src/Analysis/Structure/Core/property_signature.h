#ifndef PROPERTY_SIGNATURE_H
#define PROPERTY_SIGNATURE_H

#include <string>

#include "Interfaces/i_read_write.h"

namespace Analysis::Structure::Core
{
    class PropertySignature : public virtual Interfaces::IReadWrite
    {
        protected:
            mutable std::string getInstruction;
            mutable std::string setInstruction;

            PropertySignature();

        public:
            [[nodiscard]] virtual const std::string& SignatureGetString() const = 0;
            [[nodiscard]] virtual const std::string& SignatureSetString() const = 0;
    };
}

#endif
