#ifndef FLOAT_H
#define FLOAT_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Float final : public DataTypes::Struct, public Services::SingletonService<Float>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Float();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
