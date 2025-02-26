#ifndef PROPERTY_SIGNATURE_H
#define PROPERTY_SIGNATURE_H

#include "../Interfaces/Creation/i_property_signature.h"

namespace Analysis::Structure::Core
{
    class PropertySignature : public virtual Interfaces::IPropertySignature
    {
        protected:
            mutable std::string getInstruction;
            mutable std::string setInstruction;

            PropertySignature();
    };
}

#endif