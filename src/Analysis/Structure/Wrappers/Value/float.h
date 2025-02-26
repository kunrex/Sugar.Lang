#ifndef FLOAT_H
#define FLOAT_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Float final : public DataTypes::ValueType, public Services::SingletonService<Float>, private virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Float();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
