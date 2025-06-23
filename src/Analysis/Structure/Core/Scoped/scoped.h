#ifndef SCOPED_H
#define SCOPED_H

#include "../Interfaces/Scoped/i_scoped.h"

#include "../../Local/Variables/local_variable.h"

#include "../../../../Services/collection.h"

namespace Analysis::Structure::Core
{
    class Scoped : protected Services::ConstantCollection<Local::LocalVariable>, public virtual Interfaces::IScoped
    {
        protected:
            const ParseNodes::Core::Interfaces::IParseNode* parseNode;

            int parameterCount;
            Local::Scope* const scope;

            std::vector<std::pair<const Interfaces::IDataType*, unsigned long>> generatedIndexes;

            explicit Scoped(const ParseNodes::Core::Interfaces::IParseNode* parseNode);

        public:
            [[nodiscard]] Local::Scope* Scope() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            [[nodiscard]] unsigned long VariableCount() const override;
            [[nodiscard]] const Local::LocalVariable* VariableAt(unsigned long i) const override;

            void AddParameter(const Local::LocalVariable* parameter) override;
            void AddLocalVariable(const Local::LocalVariable* variable) override;

            [[nodiscard]] std::optional<unsigned long> GetParameterIndex(const std::string& name) const override;

            [[nodiscard]] std::pair<const Local::LocalVariable*, unsigned long> TryGetGeneratedVariable(const Interfaces::IDataType* type) override;

            ~Scoped() override;
    };
}

#endif
