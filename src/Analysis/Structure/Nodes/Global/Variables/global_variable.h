#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../global_node.h"
#include "../../Creation/Variables/variable.h"

namespace Analysis::Structure::Global
{
    class GlobalVariable final : public GlobalNode, public Creation::Variable
    {
        public:
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);

            void SetParent(const Core::DataType* parent) override;
    };
}

#endif
