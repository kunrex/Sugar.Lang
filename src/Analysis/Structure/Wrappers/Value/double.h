#ifndef DOUBLE_H
#define DOUBLE_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Double final : public DataTypes::Struct, public Services::SingletonService<Double>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Double();

        public:
            [[nodiscard]] int SlotCount() const override;

            void InitialiseMembers() override;
    };
}

#endif
