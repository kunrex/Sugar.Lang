#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Character final : public DataTypes::ValueType, public Services::SingletonService<Character>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Character();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
