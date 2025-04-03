#ifndef METHOD_FUNCTION_H
#define METHOD_FUNCTION_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/method_definition.h"

namespace Analysis::Structure::Global
{
    class MethodFunction final : public Creation::MethodDefinition, public Core::Scoped
    {
        public:
            MethodFunction(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
