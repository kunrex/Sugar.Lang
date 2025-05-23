#ifndef LOCAL_VARIABLE_H
#define LOCAL_VARIABLE_H

#include "../../Core/Creation/variable.h"

namespace Analysis::Structure::Local
{
    class LocalVariable : public Core::Variable
    {
        public:
            LocalVariable(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
