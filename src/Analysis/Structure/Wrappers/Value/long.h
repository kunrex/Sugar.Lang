#ifndef LONG_H
#define LONG_H

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Long final : public DataTypes::Struct, public Services::SingletonService<Long>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Long();

        public:
            void InitialiseMembers() override;
    };
}

#endif
