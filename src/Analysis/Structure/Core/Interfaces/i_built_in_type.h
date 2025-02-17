#ifndef I_BUILT_IN_TYPE_H
#define I_BUILT_IN_TYPE_H

namespace Analysis::Core::Interfaces
{
    class IBuiltInType
    {
        public:
            virtual void InitialiseMembers() = 0;

            virtual ~IBuiltInType() = 0;
    };
}

#endif
