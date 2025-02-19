#ifndef COMPILE_EXCEPTION_H
#define COMPILE_EXCEPTION_H

#include <string>
#include <exception>

namespace Exceptions
{
    class CompileException : public std::exception
    {
        private:
            const char* c_str;

        public:
            explicit CompileException(const std::string& message);

            [[nodiscard]] const char* what() const noexcept override;
    };
}

#endif
