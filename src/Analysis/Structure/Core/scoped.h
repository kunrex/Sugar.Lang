#ifndef SCOPED_H
#define SCOPED_H

#include "../../../Parsing/ParseNodes/Groups/scope_node.h"

#include "created.h"
#include "describable.h"

#include "../Local/Variables/local_variable.h"

namespace Analysis::Structure::Local
{
    class Scope;
}

namespace Analysis::Structure::Core
{
    class Scoped : public Services::ConstantCollection<Local::LocalVariable>, public virtual Interfaces::INode, public virtual Interfaces::IDescribable, public virtual Interfaces::ICreated
    {
        protected:
            const ParseNodes::Groups::ScopeNode* parseNode;

            mutable unsigned long parameterCount;
            mutable Local::Scope* scope;

            explicit Scoped(const ParseNodes::Groups::ScopeNode* parseNode);

        public:
            [[nodiscard]] const ParseNodes::Groups::ScopeNode* ParseNode() const;

            [[nodiscard]] unsigned long ArgumentCount() const;
            [[nodiscard]] unsigned long VariableCount() const;

            [[nodiscard]] Local::Scope* Scope() const;

            void AddParameter(const Local::LocalVariable* parameter);
            void AddLocalVariable(const Local::LocalVariable* variable);

            [[nodiscard]] std::optional<unsigned long> GetParameterIndex(const std::string& name) const;

            [[nodiscard]] const Local::LocalVariable* VariableAt(unsigned long i) const;
    };
}

#endif
