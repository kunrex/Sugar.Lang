#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../global_node.h"
#include "../../../Core/default_valued.h"
#include "../../Creation/Variables/variable.h"

namespace Analysis::Structure::Global
{
    class GlobalVariable final : public GlobalNode, public Creation::Variable, public Core::DefaultValued
    {
        public:
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
