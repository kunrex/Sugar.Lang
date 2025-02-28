#ifndef ENUM_FIELD_H
#define ENUM_FIELD_H

#include "global_variable.h"

namespace Analysis::Structure::Global
{
    class EnumField final : public GlobalVariable
    {
        public:
            explicit EnumField(const std::string& name);
            EnumField(const std::string& name, const ParseNodes::ParseNode* value);

            [[nodiscard]] bool Writable() const override;
    };
}

#endif
