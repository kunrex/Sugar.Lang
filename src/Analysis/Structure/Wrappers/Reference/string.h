#ifndef STRING_H
#define STRING_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class String final : public DataTypes::Class, public Services::SingletonService<String>, public virtual Core::Interfaces::IBuiltInType
    {
        protected:
            String();

        public:
            void InitialiseMembers() override;
    };
}

#endif
