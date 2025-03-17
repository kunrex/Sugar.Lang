#ifndef GLOBAL_CONSTANT_H
#define GLOBAL_CONSTANT_H

#include <vector>
#include <variant>

#include "global_variable.h"
#include "../../Compilation/compilation_result.h"

namespace Analysis::Structure::Global
{
    class GlobalConstant final : public GlobalVariable
    {
        private:
            std::vector<const ICharacteristic*> dependencies;
            mutable std::variant<long, double, std::string> value;

        public:
            GlobalConstant(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::ParseNode* parseNode);

            [[nodiscard]] bool Writable() const override;

            void PushDependency(const ICharacteristic* constant);
            [[nodiscard]] bool IsDependent(const ICharacteristic* constant) const;

            void WithValue(long value) const;
            void WithValue(double value) const;
            void WithValue(const std::string& value) const;

            template <typename TType>
            [[nodiscard]] std::optional<TType> Value() const;
    };
}

#endif
