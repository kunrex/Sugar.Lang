#ifndef OBJECT_H
#define OBJECT_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Object final : public DataTypes::Class, public Services::SingletonService<Object>, public virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Object();

        public:
            void InitialiseMembers() override;
    };

}

#endif
