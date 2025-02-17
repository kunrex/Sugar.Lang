#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Character final : public DataTypes::Struct, public Services::SingletonService<Character>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Character();

        public:
            void InitialiseMembers() override;
    };
}

#endif
