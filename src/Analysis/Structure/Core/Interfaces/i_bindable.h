#ifndef I_COMPILABLE_H
#define I_COMPILABLE_H

namespace Analysis::Structure::Core::Interfaces
{
    class IBindable
    {
        public:
            virtual void Bind() = 0;

            virtual ~IBindable() = default;
    };
}

#endif
