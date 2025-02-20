#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Exception final : public DataTypes::Class, public Services::SingletonService<Exception>, public Analysis::Core::Interfaces::IBuiltInType
    {
        protected:
            Exception();

        public:
            void InitialiseMembers() override;
    };
}

#endif
