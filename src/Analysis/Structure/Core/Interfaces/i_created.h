#ifndef I_CREATED_H
#define I_CREATED_H

namespace Analysis::Structure::Core::Interfaces
{
    class IDataType;

    class ICreated
    {
        public:
            [[nodiscard]] virtual const IDataType* CreationType() const = 0;

            virtual ~ICreated() = default;
    };
}

#endif
