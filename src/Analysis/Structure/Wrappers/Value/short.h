#ifndef SHORT_H
#define SHORT_H

#include "../../../../Services/singleton_service.h"

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Short final : public DataTypes::Struct, public Services::SingletonService<Short>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Short();

        public:
            void InitialiseMembers() override;
    };
}

#endif
