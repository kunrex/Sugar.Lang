#ifndef BUILT_IN_PROPERTY_H
#define BUILT_IN_PROPERTY_H

#include "../../Creation/Properties/property_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInProperty final : public Creation::PropertyDefinition
    {
        protected:
            const bool readable;
            const bool writable;

        public:
            BuiltInProperty(Enums::Describer describer, const std::string& name, const Core::Interfaces::IDataType* creationType, bool readable, const std::string& getInstruction, bool writable, const std::string& setInstruction);

            [[nodiscard]]Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;
    };
}

#endif
