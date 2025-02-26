#ifndef LONG_H
#define LONG_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Long final : public DataTypes::ValueType, public Services::SingletonService<Long>, public virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Long();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
