#ifndef BUILT_IN_VOID_H
#define BUILT_IN_VOID_H

#include "../../Creation/Functions/void_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInVoid final : public Creation::VoidDefinition
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInVoid(Enums::Describer describer, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
            [[nodiscard]] const std::string& SignatureString() const override;
            [[nodiscard]] const std::string& ArgumentSignatureString() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
