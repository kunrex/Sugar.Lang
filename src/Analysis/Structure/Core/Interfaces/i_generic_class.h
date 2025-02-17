#ifndef I_GENERIC_CLASS_H
#define I_GENERIC_CLASS_H

namespace Analysis::Structure::Core::Interfaces
{
    class IGenericClass
    {
        public:
            [[nodiscard]] virtual const std::string& GenericSignature() const = 0;

            virtual ~IGenericClass() = 0;
    };
}

#endif
