#ifndef SOURCE_DIRECTORY_H
#define SOURCE_DIRECTORY_H

#include "source_object.h"
#include "../../Services/dictionary.h"

namespace Analysis::Structure
{
    class SourceDirectory final : public SourceObject, public Services::Dictionary<std::string, SourceObject>
    {
        public:
            explicit SourceDirectory(const std::string& name);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            bool Push(std::string key, SourceObject* value) override;

            void ReferenceThis(SourceObject* other) override;
            void AddReference(const Core::DataType* dataType) override;
    };
}

#endif
