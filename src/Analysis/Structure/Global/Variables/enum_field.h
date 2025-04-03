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
            mutable bool compiled;
            mutable std::vector<const IConstant*> dependencies;
            mutable std::variant<long, double, std::string> value;

        public:
            EnumField(const std::string& name, Enums::Describer describer);
            EnumField(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* parseNode);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            void PushDependency(const IConstant* constant) const override;
            [[nodiscard]] bool IsDependent(const IConstant* constant) const override;

            void Compile(Compilation::CompilationResult result) const override;
            [[nodiscard]] Compilation::CompilationResult AsCompilationResult() const override;
    };
}

#endif
