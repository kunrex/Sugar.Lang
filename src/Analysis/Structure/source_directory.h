#ifndef SOURCE_DIRECTORY_H
#define SOURCE_DIRECTORY_H

#include "source_object.h"
#include "../../Services/collection.h"

namespace Analysis::Structure
{
    class SourceDirectory final : public SourceObject, public Services::Collection<SourceObject>
    {
        public:
            explicit SourceDirectory(const std::string& name);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            void AddChild(SourceObject* child) override;

            void ReferenceThis(SourceObject* other) override;
            void AddReference(const Core::DataType* dataType) override;
    };
}

#endif
