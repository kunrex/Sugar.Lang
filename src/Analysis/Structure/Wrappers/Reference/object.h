#ifndef OBJECT_H
#define OBJECT_H

#include "../../Nodes/DataTypes/class.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class Object final : public DataTypes::Class, public Services::SingletonService<Object>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Object();

        public:
            void InitialiseMembers() override;
    };

}

#endif
