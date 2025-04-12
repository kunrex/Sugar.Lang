#ifndef SOURCE_DIRECTORY_H
#define SOURCE_DIRECTORY_H

#include "../../Services/dictionary.h"

#include "source_object.h"

namespace Analysis::Structure
{
    class SourceDirectory final : public SourceObject, public Services::Dictionary<std::string, SourceObject>
    {
        public:
            explicit SourceDirectory(const std::string& name);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            bool AddChild(std::string key, SourceObject* value) override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
