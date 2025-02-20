#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Global
{
    class GlobalVariable : public Core::Characteristic
    {
        public:
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
