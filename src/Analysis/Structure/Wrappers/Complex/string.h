
#ifndef STRING_H
#define STRING_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"

namespace Analysis::Structure::Wrappers
{
    class String final : public DataTypes::Class, public Services::SingletonService<String>
    {
        protected:
            String();

        public:
            void InitialiseMembers();
    };
}

#endif
