#ifndef I_FUNCTION_H
#define I_FUNCTION_H

namespace Analysis::Structure::Core::Interfaces
{
    class IFunction
    {
        public:
            [[nodiscard]] virtual unsigned long ParameterCount() const = 0;
            [[nodiscard]] virtual const DataType* ParameterAt(unsigned long index) const = 0;

            virtual ~IFunction() = 0;
    };
}

#endif
