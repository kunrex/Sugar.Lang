#ifndef DOUBLE_H
#define DOUBLE_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Double final : public DataTypes::ValueType, public Services::SingletonService<Double>, private virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Double();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
