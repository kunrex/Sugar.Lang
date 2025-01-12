#ifndef DESCRIBABLE_H
#define DESCRIBABLE_H

#include "../Enums/describer.h"

namespace Analysis::Structure::Core
{
    class Describable
    {
        protected:
            const Enums::Describer describer;

            explicit Describable(Enums::Describer describer);

        public:
            [[nodiscard]] Enums::Describer Describer() const;

            [[nodiscard]] bool CheckDescriber(Enums::Describer describer) const;
            [[nodiscard]] bool ValidateDescriber(Enums::Describer allowed) const;
    };
}

#endif
