#include "string_builder.h"

#include <format>
#include <fstream>
#include <iostream>
#include <utility>

#include "../Exceptions/exception_manager.h"
#include "../Exceptions/Compilation/transpile_file_exception.h"

using namespace std;
namespace fs = std::filesystem;

using namespace Exceptions;

namespace Services
{
    StringBuilder::StringBuilder(string outputFile) : value(), outputFile(std::move(outputFile))
    { }

    const std::string& StringBuilder::OutputFile() const { return outputFile; }

    void StringBuilder::IncreaseIndent() { indent++; }

    void StringBuilder::DecreaseIndent() { indent--; }

    void StringBuilder::PushLine(const std::string& content)
    {
        value += std::format("{}{}\n", string(indent, '\t'), content);
    }

    void StringBuilder::PushValueToFile()
    {
        if (std::ofstream file(outputFile); file.is_open())
        {
            file << value;
            file.close();

            value.clear();
        }
        else
            ExceptionManager::Instance().AddChild(new TranspileFileException(string(outputFile)));
    }
}
