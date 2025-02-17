#ifndef SOURCE_OBJECT_H
#define SOURCE_OBJECT_H

#include "Core/nameable.h"
#include "Enums/source_type.h"
#include "../../Services/child.h"

namespace Analysis::Structure::Core
{
    class DataType;
}

namespace Analysis::Structure
{
    class SourceObject : public Services::Child<SourceObject>, public Core::Nameable
    {
        public:
            explicit SourceObject(const std::string& name);

            [[nodiscard]] virtual Enums::SourceType SourceType() const = 0;

            virtual void ReferenceThis(SourceObject* other) = 0;
            virtual void AddReference(const Core::DataType* dataType) = 0;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
