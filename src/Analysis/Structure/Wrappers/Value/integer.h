#ifndef INTEGER_H
#define INTEGER_H

#include "../../../../Services/singleton_service.h"

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Integer final : public DataTypes::Struct, public Services::SingletonService<Integer>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Integer();

        public:
            void InitialiseMembers() override;
    };
}

#endif
