#ifndef I_NAMEABLE_H
#define I_NAMEABLE_H

namespace Analysis::Structure::Core::Interfaces
{
    class INameable
    {
        public:
            [[nodiscard]] virtual const std::string& Name() const = 0;

            virtual ~INameable() = default;
    };
}

#endif
