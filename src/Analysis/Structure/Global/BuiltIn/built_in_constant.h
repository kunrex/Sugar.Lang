#ifndef BUILT_IN_CONSTANT_H
#define BUILT_IN_CONSTANT_H

#include "../../Core/Creation/characteristic.h"
#include "../../Core/Interfaces/Creation/i_constant.h"

namespace Analysis::Structure::Global
{
    class BuiltInConstant final : public Core::Characteristic, public virtual Core::Interfaces::IConstant
    {
        public:
            BuiltInConstant(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IContextNode* context);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool Compiled() const override;

            void PushDependency(const IConstant* constant) const override;
            [[nodiscard]] bool IsDependent(const IConstant* constant) const override;

            void BindLocal() override;
    };
}

#endif
