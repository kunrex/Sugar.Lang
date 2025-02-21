#include "cil_transpiler.h"

#include <format>
#include <fstream>
#include <filesystem>

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/transpile_file_exception.h"
#include "../../../Exceptions/Compilation/Analysis/ambiguous_import_exception.h"
#include "../../Structure/Core/DataTypes/data_type.h"
#include "../../Structure/Nodes/Context/context_node.h"

using namespace std;
namespace fs = filesystem;

using namespace Services;

using namespace Exceptions;

using namespace Analysis::Structure;
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
    std::optional<std::string> CreateOutputFile(const std::string& outputDirectory, const std::string& fileName)
    {
        const auto outputFile = outputDirectory / fs::path(fileName);

        if (std::ofstream file(outputFile); file.is_open())
        {
            file.close();
            return string(outputFile);
        }

        ExceptionManager::Instance().AddChild(new TranspileFileException(outputFile));
        return std::nullopt;
    }

    CILTranspiler::CILTranspiler(string name, string directory, const SourceDirectory* const source) : projectName(std::move(name)), projectDirectory(std::move(directory)), source(source), initialised(false)
    {
        const auto outputDirectory = fs::path(std::format("{}/{}/bin", projectDirectory, projectName));
        if (!exists(outputDirectory))
        {
            if (create_directories(outputDirectory))
                std::cout << "Output directory created: " << outputDirectory << std::endl;
            else
            {
                ExceptionManager::Instance().AddChild(new TranspileFileException(outputDirectory));
                return;
            }
        }

        std::string outputFile;
        if (const auto programSource = source->GetChild("program"); programSource != nullptr)
        {
            const auto sourceFile = dynamic_cast<const SourceFile*>(programSource);

            if (const auto programFile = sourceFile->GetChild("Program"); programFile != nullptr)
            {
                if (const auto main = programFile->FindFunction("Main", std::vector<const DataType*>()); main != nullptr && main->CheckDescriber(Describer::PublicStatic))
                {
                    isExecutable = true;
                    outputFile = std::format("{}.{}", projectName, "exe");
                }
            }
        }

        if (outputFile.empty())
            outputFile = std::format("{}.{}", projectName, "dll");

        if (const auto result = CreateOutputFile(outputDirectory, outputFile); result)
            stringBuilder = new StringBuilder(*result);
    }

    void CILTranspiler::Transpile()
    {
        if (isExecutable)
        {
            //map program
        }
    }

    void CILTranspiler::TranspileDirectory(const SourceDirectory* const directory)
    {
        for (const auto child: directory->values())
        {
            if (child->SourceType() == SourceType::File)
                TranspileFile(dynamic_cast<const SourceFile*>(child));
            else
                TranspileDirectory(dynamic_cast<const SourceDirectory*>(child));
        }
    }

    void CILTranspiler::TranspileFile(const SourceFile* file)
    {
        for (const auto type : file->values())
            TranspileDataType(type);
    }

    void CILTranspiler::TranspileDataType(const DataType* const dataType)
    {
        switch (dataType->MemberType())
        {
            case MemberType::Enum:
                stringBuilder->PushLine(std::format(".class {} {} {} {} {} {} {}", dataType->Describer(), prefix_auto, prefix_ansi, prefix_sealed, dataType->Name(), prefix_extends, ms_core_enum));
                break;
            case MemberType::Class:
                stringBuilder->PushLine(std::format(".class {} {} {} {} {} {} {}", dataType->Describer(), prefix_auto, prefix_ansi, prefix_sealed, dataType->Name(), prefix_extends, ms_core_class));
                break;
            case MemberType::ValueType:
                stringBuilder->PushLine(std::format(".class {} {} {} {} {} {} {}", dataType->Describer(), prefix_auto, prefix_ansi, prefix_sealed, dataType->Name(), prefix_extends, ms_core_struct));
                break;
            default:
                break;
        }

        stringBuilder->PushLine(open_flower);
        stringBuilder->IncreaseIndent();

        for (const auto characteristic: dataType->AllCharacteristics())
        {
            //create characteristics
        }

        for (const auto characteristic: dataType->AllFunctions())
        {
            //create functions
        }

        stringBuilder->DecreaseIndent();
        stringBuilder->PushLine(close_flower);
    }

    void CILTranspiler::Expression()
    {

    }

    CILTranspiler::~CILTranspiler()
    {
        delete stringBuilder;
    }
}
