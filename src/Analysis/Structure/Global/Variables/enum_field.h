#ifndef ENUM_FIELD_H
#define ENUM_FIELD_H

#include "global_variable.h"

namespace Analysis::Structure::Global
{
    class EnumField final : public GlobalVariable
    {
        private:
            const Core::Interfaces::IDataType* returnType;

        public:
            EnumField(const std::string& name, const Core::Interfaces::IDataType* returnType);
            EnumField(const std::string& name, const Core::Interfaces::IDataType* returnType, const ParseNodes::ParseNode* value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] const Core::Interfaces::IDataType* ReturnType() const;
    };
}

#endif
