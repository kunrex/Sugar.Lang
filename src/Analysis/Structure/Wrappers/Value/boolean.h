#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Boolean final : public DataTypes::ValueType, public Services::SingletonService<Boolean>, private virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Boolean();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
