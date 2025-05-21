#ifndef I_COMPILABLE_H
#define I_COMPILABLE_H

namespace Analysis::Structure::Core::Interfaces
{
    class ILocallyBindable
    {
        public:
            virtual void BindLocal() = 0;

            virtual ~ILocallyBindable() = default;
    };

    class IGloballyBindable
    {
        public:
            virtual void BindGlobal() = 0;

            virtual ~IGloballyBindable() = default;
    };
}

#endif
