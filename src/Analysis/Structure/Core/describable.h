#ifndef DESCRIBABLE_H
#define DESCRIBABLE_H

#include "Interfaces/i_describable.h"

namespace Analysis::Structure::Core
{
    class Describable : public virtual Interfaces::IDescribable
    {
        protected:
            const Enums::Describer describer;

            explicit Describable(Enums::Describer describer);

        public:
            [[nodiscard]] Enums::Describer Describer() const override;

            [[nodiscard]] bool ValidateDescriber(Enums::Describer allowed) const override;

            [[nodiscard]] bool MatchDescriber(Enums::Describer expected) const override;
            [[nodiscard]] bool CheckDescriber(Enums::Describer describer) const override;
    };
}

#endif
