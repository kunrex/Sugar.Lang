#ifndef I_SCOPED_H
#define I_SCOPED_H

#include "../i_nameable.h"
#include "../Creation/i_function.h"

#include "../../../Local/Variables/local_variable.h"

namespace Analysis::Structure::Local
{
    class Scope;
}

namespace Analysis::Structure::Core::Interfaces
{
    class IScoped : public virtual IFunction, public virtual INameable
    {
        public:
            [[nodiscard]] virtual const ParseNodes::Core::Interfaces::IParseNode* ParseNode() const = 0;

            [[nodiscard]] virtual Local::Scope* Scope() const = 0;

            [[nodiscard]] virtual unsigned long VariableCount() const = 0;
            [[nodiscard]] virtual const Local::LocalVariable* VariableAt(unsigned long i) const = 0;

            virtual void AddParameter(const Local::LocalVariable* parameter) = 0;
            virtual void AddLocalVariable(const Local::LocalVariable* variable) = 0;

            [[nodiscard]] virtual std::optional<unsigned long> GetParameterIndex(const std::string& name) const = 0;
    };
}

#endif
