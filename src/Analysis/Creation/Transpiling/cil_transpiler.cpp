#include "cil_transpiler.h"

#include <format>
#include <fstream>
#include <filesystem>

#include "../../Structure/Core/DataTypes/data_type.h"
#include "../../Structure/Nodes/Context/context_node.h"

using namespace std;
namespace fs = filesystem;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

constexpr string open_flower = "\n{\n\t";
constexpr string close_flower = "\n}\n";

constexpr string prefix_auto = "auto";
constexpr string prefix_ansi = "ansi";
constexpr string prefix_sealed = "sealed";
constexpr string prefix_extends = "extends";
constexpr string prefix_sequential = "sequential";
constexpr string prefix_before = "beforefieldinit";

constexpr string ms_core_enum = "[mscorlib]System.Enum";
constexpr string ms_core_class = "[mscorlib]System.Object";
constexpr string ms_core_struct = "[mscorlib]System.TypeValue";

namespace Analysis::Creation
{
    CILTranspiler::CILTranspiler(string name, string directory) : projectName(std::move(name)), projectDirectory(std::move(directory)), source()
    { }

    bool CILTranspiler::TryCreateFile() const
    {
        const fs::path file_name = std::format("{}.exe", projectName);
        const fs::path directory = std::format("{}/bin", projectDirectory);
        fs::path file_path = directory / file_name;

        if (!exists(directory))
        {
            if (!create_directories(directory))
            {
                std::cerr << "Failed to bin at: " << directory << std::endl;
                return false;
            }
        }

        std::ofstream file(file_path);
        if (file.is_open())
        {
            file << "This is a file in a new directory.\n";
            file.close();
            std::cout << "File created successfully: " << file_path << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Failed to create file: " << file_path << std::endl;
            return false;
        }
    }

    void CILTranspiler::Transpile(const SourceDirectory* directory)
    {

    }

    void CILTranspiler::TranspileFile(const SourceFile* file)
    {
        for (const auto type : *file)
            TranspileDataType(type);
    }

    void CILTranspiler::TranspileDirectory(const SourceDirectory* directory)
    {
        for (const auto child: *directory)
        {
            if (child->SourceType() == SourceType::File)
                TranspileFile(dynamic_cast<const SourceFile*>(child));
            else
                TranspileDirectory(dynamic_cast<const SourceDirectory*>(child));
        }
    }

    void CILTranspiler::TranspileDataType(const DataType* dataType)
    {
        switch (dataType->MemberType())
        {
            case MemberType::Enum:
                source += std::format(".class {} {} {} {} {} {} {}", dataType->Describer(), prefix_auto, prefix_ansi, prefix_sealed, dataType->Name(), prefix_extends, ms_core_enum);
                break;
            case MemberType::Class:
                source += std::format(".class {} {} {} {} {} {} {} {}", dataType->Describer(), prefix_auto, prefix_ansi, prefix_before, prefix_sealed, dataType->Name(), prefix_extends, ms_core_class);
                break;
            case MemberType::Struct:
                source += std::format(".class {} {} {} {} {} {} {}", dataType->Describer(), prefix_sequential, prefix_ansi, prefix_sealed, dataType->Name(), prefix_extends, ms_core_struct);
                break;
        }

        source += open_flower;
        //transpile everything else
        source += close_flower;
    }

    void CILTranspiler::Expression()
    {

    }
}
