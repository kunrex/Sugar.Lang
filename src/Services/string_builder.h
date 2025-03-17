#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <string>

namespace Services
{
    class StringBuilder final
    {
        private:
            int indent = 0;
            std::string value;

        public:
            StringBuilder();

            [[nodiscard]] int Indent() const;
            [[nodiscard]] std::string Value() const;

            void IncreaseIndent();
            void DecreaseIndent();

            void SetIndent(int indent);

            void Push(const std::string& content);
            void PushLine(const std::string& content);
    };
}

#endif
