#ifndef SCOPE_H
#define SCOPE_H

#include "../local_node.h"
#include "../../../../../Services/collection.h"
#include "../../../../../Services/dictionary.h"
#include "../../../Core/scoped.h"
#include "../../../Enums/scope_type.h"
#include "../../Context/context_node.h"
#include "../Variables/local_variable.h"

namespace Analysis::Structure::Local
{
    class Scope final : public LocalNode, public Core::FullyNameable, Services::ConstantChild<Scope>, public Services::ConstantCollection<Context::ContextNode>
    {
        private:
            const Enums::ScopeType type;

            Core::Scoped* const scoped;

            std::vector<const Scope*> nested;
            std::unordered_map<std::string, int> variableIndices;

        public:
            Scope(Enums::ScopeType type, const std::string& name, Core::Scoped* scoped);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] Enums::ScopeType Type() const;

            void AddVariable(const LocalVariable* variable);
            [[nodiscard]] int GetVariable(const std::string& name) const;

            void AddNested(Scope* scope);
            [[nodiscard]] int NestedCount() const;
            [[nodiscard]] const Scope* NestedAt(int index) const;

            [[nodiscard]] const std::string& FullName() const override;

            ~Scope() override;
    };
}


#endif
