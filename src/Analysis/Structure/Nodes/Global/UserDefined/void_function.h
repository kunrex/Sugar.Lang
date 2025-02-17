#ifndef VOID_FUNCTION_H
#define VOID_FUNCTION_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/void_definition.h"

namespace Analysis::Structure::Global
{
    class VoidFunction final : public Creation::VoidDefinition, public Core::Scoped
    {
        public:
            VoidFunction(const std::string& name, Enums::Describer describer, const ParseNodes::Groups::ScopeNode* body);

            void AddArgument(const Local::LocalVariable* parameter) override;
    };
}

#endif
