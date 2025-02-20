#ifndef LOCAL_VARIABLE_H
#define LOCAL_VARIABLE_H

#include "../local_node.h"

#include "../../Core/Creation/variable.h"

namespace Analysis::Structure::Local
{
    class LocalVariable : public LocalNode, public Core::Variable
    {
        public:
            LocalVariable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
