#ifndef SCOPE_H
#define SCOPE_H

#include <optional>
#include <unordered_map>

#include "../../../../Services/collection.h"

#include "../local_node.h"
#include "../Variables/local_variable.h"

#include "../../Core/scoped.h"
#include "../../Enums/scope_type.h"
#include "../../Context/context_node.h"

namespace Analysis::Structure::Local
{
    class Scope final : public LocalNode, public Core::Nameable, Services::ConstantChild<Scope>, public Services::ConstantCollection<Context::ContextNode>
    {
        private:
            const Enums::ScopeType type;

            Core::Scoped* const scoped;

            std::vector<const Scope*> nested;
            std::unordered_map<std::string, unsigned long> variableIndices;

        public:
            Scope(Enums::ScopeType type, const std::string& name, Core::Scoped* scoped);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] Enums::ScopeType Type() const;

            void AddVariable(const LocalVariable* variable);
            [[nodiscard]] std::optional<unsigned long> GetVariable(const std::string& name) const;

            void AddNested(Scope* scope);
            [[nodiscard]] unsigned long NestedCount() const;
            [[nodiscard]] const Scope* NestedAt(unsigned long index) const;

            ~Scope() override;
    };
}


#endif
