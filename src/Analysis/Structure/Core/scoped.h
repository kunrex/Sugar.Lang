#ifndef SCOPED_H
#define SCOPED_H

#include "../Local/Variables/local_variable.h"

namespace Analysis::Structure::Local
{
    class Scope;
}

namespace Analysis::Structure::Core
{
    class Scoped : public Services::ConstantCollection<Local::LocalVariable>, public virtual Interfaces::INode, public virtual Interfaces::IDescribable, public virtual Interfaces::ICreated, public virtual Interfaces::IParametrized
    {
        protected:
            const ParseNodes::NodeCollection<ParseNodes::ParseNode>* parseNode;

            mutable unsigned long parameterCount;
            mutable Local::Scope* scope;

            explicit Scoped(const ParseNodes::NodeCollection<ParseNodes::ParseNode>* parseNode);

        public:
            [[nodiscard]] const ParseNodes::NodeCollection<ParseNodes::ParseNode>* ParseNode() const;

            [[nodiscard]] Local::Scope* Scope() const;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            [[nodiscard]] unsigned long VariableCount() const;
            [[nodiscard]] const Local::LocalVariable* VariableAt(unsigned long i) const;

            void AddParameter(const Local::LocalVariable* parameter);
            void AddLocalVariable(const Local::LocalVariable* variable);

            [[nodiscard]] std::optional<unsigned long> GetParameterIndex(const std::string& name) const;
    };
}

#endif
