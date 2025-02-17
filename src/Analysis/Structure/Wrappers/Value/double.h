#ifndef DOUBLE_H
#define DOUBLE_H

#include "../../Nodes/DataTypes/struct.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Double final : public DataTypes::Struct, public Services::SingletonService<Double>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Double();

        public:
            void InitialiseMembers() override;
    };
}

#endif
