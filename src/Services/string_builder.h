#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <string>

namespace Services
{
    class StringBuilder final
    {
        private:
            std::string value;
            const std::string outputFile;

            int indent = 0;

        public:
            explicit StringBuilder(std::string outputFile);

            [[nodiscard]] const std::string& OutputFile() const;

            void IncreaseIndent();
            void DecreaseIndent();

            void PushLine(const std::string& content);
            void PushValueToFile();
    };
}

#endif
