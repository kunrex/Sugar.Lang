#ifndef DEFAULT_SCOPED_H
#define DEFAULT_SCOPED_H

#include "../../Local/Scopes/scope.h"

#include "../Interfaces/Scoped/i_scoped.h"

namespace Analysis::Structure::Core
{
    class DefaultScoped final : public Describable, public virtual Interfaces::IScoped
    {
        private:
            mutable Local::Scope scope;

        public:
            explicit DefaultScoped(Enums::Describer describer);

            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseNode() const override;

            [[nodiscard]] Local::Scope* Scope() const override;

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& Name() const override;
            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] const Interfaces::IDataType* CreationType() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            [[nodiscard]] unsigned long VariableCount() const override;
            [[nodiscard]] const Local::LocalVariable* VariableAt(unsigned long i) const override;

            void AddParameter(const Local::LocalVariable* parameter) override;
            void AddLocalVariable(const Local::LocalVariable* variable) override;

            [[nodiscard]] std::optional<unsigned long> GetParameterIndex(const std::string& name) const override;
    };
}

#endif
