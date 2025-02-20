#ifndef I_DESCRIBABLE_H
#define I_DESCRIBABLE_H

#include "../../Enums/describer.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IDescribable
    {
        public:
            [[nodiscard]] virtual bool ValidateDescriber(Enums::Describer allowed) const = 0;

            [[nodiscard]] virtual bool MatchDescriber(Enums::Describer expected) const = 0;
            [[nodiscard]] virtual bool CheckDescriber(Enums::Describer describer) const = 0;

            virtual ~IDescribable() = default;
    };
}

#endif
