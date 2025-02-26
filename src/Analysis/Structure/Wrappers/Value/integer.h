#ifndef INTEGER_H
#define INTEGER_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Integer : public DataTypes::ValueType, public Services::SingletonService<Integer>, private virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Integer();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
