#ifndef SCOPED_H
#define SCOPED_H

#include "../Nodes/Local/Variables/local_variable.h"
#include "../../../Parsing/ParseNodes/Groups/scope_node.h"

namespace Analysis::Structure::Local
{
    class Scope;
}

namespace Analysis::Structure::Core
{
    class Scoped : public virtual Describable, Services::ConstantCollection<Local::LocalVariable>
    {
        protected:
            const ParseNodes::Groups::ScopeNode* parseNode;

            mutable int argumentCount;
            mutable Local::Scope* scope;

            explicit Scoped(const ParseNodes::Groups::ScopeNode* parseNode);

        public:
            [[nodiscard]] const ParseNodes::Groups::ScopeNode* ParseNode() const;

            [[nodiscard]] int ArgumentCount() const;
            [[nodiscard]] int VariableCount() const;

            [[nodiscard]] Local::Scope* Scope() const;

            virtual void AddArgument(const Local::LocalVariable* parameter);
            void AddLocalVariable(const Local::LocalVariable* variable);

            [[nodiscard]] bool ContainsArgument(const std::string& name) const;
            [[nodiscard]] int GetArgument(const std::string& name) const;

            [[nodiscard]] const Local::LocalVariable* VariableAt(int i) const;
    };
}

#endif
