#ifndef I_DELEGATE_TYPE_H
#define I_DELEGATE_TYPE_H

#include "i_data_type.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IDelegateType : public virtual IDataType
    {
        public:
            [[nodiscard]] virtual const std::string& DelegateSignature() const = 0;
    };
}

#endif
