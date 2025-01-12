#ifndef METHOD_FUNCTION_H
#define METHOD_FUNCTION_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/method_definition.h"

namespace Analysis::Structure::Global
{
    class MethodFunction final : public Creation::MethodDefinition, public Core::Scoped
    {
        public:
            MethodFunction(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* body);

            void SetParent(const Core::DataType* parent) override;

            bool operator<(const MethodFunction& rhs) const;
    };
}

#endif
