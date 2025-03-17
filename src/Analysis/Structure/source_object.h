#ifndef SOURCE_OBJECT_H
#define SOURCE_OBJECT_H

#include "../../Services/child.h"

#include "Core/nameable.h"
#include "Enums/source_type.h"

namespace Analysis::Structure
{
    class SourceObject : public Core::Nameable, public Services::Child<SourceObject>
    {
        protected:
            mutable std::string fullName;

        public:
            explicit SourceObject(const std::string& name);

            [[nodiscard]] virtual Enums::SourceType SourceType() const = 0;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
