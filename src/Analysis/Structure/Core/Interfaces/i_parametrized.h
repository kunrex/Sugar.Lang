#ifndef I_PARAMETERIZED_H
#define I_PARAMETERIZED_H

namespace Analysis::Structure::Core::Interfaces
{
    class IParametrized
    {
        public:
            [[nodiscard]] virtual unsigned long ParameterCount() const = 0;
            [[nodiscard]] virtual const DataType* ParameterAt(unsigned long index) const = 0;

            virtual ~IParametrized() = default;
    };
}

#endif
