#include "string_builder.h"

#include <format>
#include <fstream>

#include "../Exceptions/Compilation/transpile_file_exception.h"

using namespace std;

using namespace Exceptions;

namespace Services
{
    StringBuilder::StringBuilder() = default;

    StringBuilder::StringBuilder(std::string fileLocation) : fileLocation(std::move(fileLocation))
    { }

    int StringBuilder::Indent() const { return indent; }

    const string& StringBuilder::Value() const { return value; }

    void StringBuilder::IncreaseIndent() { indent++; }

    void StringBuilder::DecreaseIndent() { indent--; }

    void StringBuilder::SetIndent(const int indent) { this->indent = indent; }

    void StringBuilder::Push(const std::string& content)
    {
        value.append(content);
    }

    void StringBuilder::PushLine(const std::string& content)
    {
        value.append(std::format("{}{}\n", string(indent, '\t'), content));
    }

    void StringBuilder::PushLine(const std::string_view& content)
    {
        value.append(std::format("{}{}\n", string(indent, '\t'), content));
    }

    void StringBuilder::WriteToFile()
    {
        if (fileLocation.empty())
            return;

        std::ofstream output(fileLocation);
        if (!output.is_open())
            return;

        output << value << std::endl;
        output.close();

        value.clear();
    }

    void StringBuilder::Clear()
    {
        value.clear();
    }
}
