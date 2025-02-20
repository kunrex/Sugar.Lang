#ifndef LONG_H
#define LONG_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Long final : public DataTypes::Struct, public Services::SingletonService<Long>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Long();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
