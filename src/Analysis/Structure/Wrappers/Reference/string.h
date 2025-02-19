#ifndef STRING_H
#define STRING_H

#include "../../../../Services/singleton_service.h"

#include "../../Nodes/DataTypes/class.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class String final : public DataTypes::Class, public Services::SingletonService<String>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            String();

        public:
            void InitialiseMembers() override;
    };
}

#endif
