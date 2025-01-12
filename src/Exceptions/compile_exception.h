#ifndef COMPILE_EXCEPTION_H
#define COMPILE_EXCEPTION_H

#include <string>
#include <exception>

namespace Exceptions
{
    class CompileException : public std::exception
    {
        protected:
            const std::string message;

            explicit CompileException(std::string message);

        public:
            [[nodiscard]] const char* what() const noexcept override;
    };
}

#endif
