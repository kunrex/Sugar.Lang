#ifndef PROPERTY_H
#define PROPERTY_H

#include "../../Creation/Functions/void_definition.h"
#include "../../Creation/Functions/method_definition.h"
#include "../../Creation/Properties/property_definition.h"

namespace Analysis::Structure::Global
{
    class Property final : public Creation::PropertyDefinition
    {
        private:
            mutable bool readable;
            mutable std::string getInstruction;

            mutable bool writable;
            mutable std::string setInstruction;

        public:
            Property(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Creation::MethodDefinition* get, const Creation::VoidDefinition* set);
            Property(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Creation::MethodDefinition* get, const Creation::VoidDefinition* set, const ParseNodes::ParseNode* value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;;
    };
}

#endif
