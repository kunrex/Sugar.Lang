#ifndef MATH_H
#define MATH_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Math final : public DataTypes::Class, public Services::SingletonService<Math>, public virtual Core::Interfaces::IBuiltInType
    {
        protected:
            Math();

        public:
            void InitialiseMembers() override;
    };
}

#endif
