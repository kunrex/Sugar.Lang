#ifndef ENUM_CONSTANT_H
#define ENUM_CONSTANT_H

#include "global_variable.h"

namespace Analysis::Structure::Global
{
    class EnumConstant final : public GlobalVariable
    {
        public:
            explicit EnumConstant(const std::string& name);
            EnumConstant(const std::string& name, const ParseNodes::ParseNode* value);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
