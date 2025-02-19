#ifndef FLOAT_H
#define FLOAT_H

#include "../../../../Services/singleton_service.h"

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Float final : public DataTypes::Struct, public Services::SingletonService<Float>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Float();

        public:
            void InitialiseMembers() override;
    };
}

#endif
