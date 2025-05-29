#ifndef DEFAULT_SCOPED_H
#define DEFAULT_SCOPED_H

#include "../../Local/Scopes/scope.h"

#include "../Interfaces/Scoped/i_scoped.h"

namespace Analysis::Structure::Core
{
    class DefaultScoped : public virtual Interfaces::IScoped
    {
        private:
            Local::Scope* const scope;

        public:
            DefaultScoped();

            [[nodiscard]] Local::Scope* Scope() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            [[nodiscard]] unsigned long VariableCount() const override;
            [[nodiscard]] const Local::LocalVariable* VariableAt(unsigned long i) const override;

            void AddParameter(const Local::LocalVariable* parameter) override;
            void AddLocalVariable(const Local::LocalVariable* variable) override;

            [[nodiscard]] std::optional<unsigned long> GetParameterIndex(const std::string& name) const override;

            ~DefaultScoped() override;
    };
}

#endif
