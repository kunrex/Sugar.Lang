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

            const std::string fileLocation;

        public:
            StringBuilder();
            explicit StringBuilder(std::string fileLocation);

            [[nodiscard]] int Indent() const;
            [[nodiscard]] const std::string& Value() const;

            void IncreaseIndent();
            void DecreaseIndent();

            void SetIndent(int indent);

            void Push(const std::string& content);
            void PushLine(const std::string& content = "");
            void PushLine(const std::string_view& content = "");

            void WriteToFile();

            void Clear();
    };
}

#endif
