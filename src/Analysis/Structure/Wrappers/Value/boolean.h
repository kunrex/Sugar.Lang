#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Boolean final : public DataTypes::Struct, public Services::SingletonService<Boolean>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Boolean();

        public:
            void InitialiseMembers() override;
    };
}

#endif
