#ifndef I_READ_WRITE_H
#define I_READ_WRITE_H

namespace Analysis::Structure::Core::Interfaces
{
    class IReadWrite
    {
        public:
            [[nodiscard]] virtual bool Readable() const = 0;
            [[nodiscard]] virtual bool Writable() const = 0;

            virtual ~IReadWrite();
    };
}

#endif
