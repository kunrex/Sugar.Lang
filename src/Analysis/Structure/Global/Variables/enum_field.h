#ifndef ENUM_FIELD_H
#define ENUM_FIELD_H

#include <vector>

#include "global_variable.h"

#include "../../Core/Interfaces/Creation/i_constant.h"

namespace Analysis::Structure::Global
{
    class EnumField final : public GlobalVariable, public virtual Core::Interfaces::IConstant
    {
        private:
            bool compiled;
            std::vector<const ICharacteristic*> dependencies;

        public:
            EnumField(const std::string& name, Enums::Describer describer);
            EnumField(const std::string& name, Enums::Describer describer, const ParseNodes::ParseNode* parseNode);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            void Compile(const std::string& value) override;

            void PushDependency(const ICharacteristic* constant) override;
            [[nodiscard]] bool IsDependent(const ICharacteristic* constant) const override;
    };
}

#endif
