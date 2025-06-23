#include "string_builder.h"

#include <format>
#include <fstream>
#include <iostream>
#include <utility>

#include "../Exceptions/exception_manager.h"
#include "../Exceptions/Compilation/transpile_file_exception.h"

using namespace std;

using namespace Exceptions;

namespace Services
{
    StringBuilder::StringBuilder() = default;

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

    void StringBuilder::Clear()
    {
        value.clear();
    }
}
