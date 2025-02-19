#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Boolean final : public DataTypes::Struct, public Services::SingletonService<Boolean>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Boolean();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
