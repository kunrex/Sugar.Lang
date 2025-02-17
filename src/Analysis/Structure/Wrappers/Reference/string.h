#ifndef STRING_H
#define STRING_H

#include "../../Nodes/DataTypes/class.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../../../Services/singleton_service.h"

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
