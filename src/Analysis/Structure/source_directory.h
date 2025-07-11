#ifndef SOURCE_DIRECTORY_H
#define SOURCE_DIRECTORY_H

#include "source_object.h"

#include "../../Services/dictionary.h"

namespace Analysis::Structure
{
    class SourceDirectory final : public SourceObject, public Services::Dictionary<std::string, SourceObject>
    {
        public:
            SourceDirectory(const std::string& name, bool isRoot);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            bool AddChild(std::string key, SourceObject* value) override;

            void LexParse() override;
            void InitDataTypes() override;
            void ManageImports() override;

            void BindGlobal() override;
            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
