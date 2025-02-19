#include "project_binder.h"

#include <regex>
#include <sstream>

#include "binder_extensions.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Project/ambiguous_import_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Project/invalid_import_path_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Project/duplicate_structure_definition_exception.h"

#include "../../Structure/source_directory.h"

#include "../../Structure/DataTypes/enum.h"
#include "../../Structure/DataTypes/class.h"
#include "../../Structure/DataTypes/struct.h"

using namespace Exceptions;

using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Describers;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;

constexpr char delimiter = '.';
const auto pathRegex = std::regex(R"(^(\.)*(?:[a-zA-Z0-9_-]+(?:\.[a-zA-Z0-9_-]+)*)?$)");

namespace Analysis::Creation::Binding
{
    void CreateEnum(const DataTypeNode* const node, SourceFile* const sourceFile)
    {
        const auto index = node->Index();
        const auto identifier = node->Name()->Value();

        if (sourceFile->GetChild(identifier) != nullptr)
        {
            PushException(new DuplicateStructureDefinitionException(index, sourceFile));
            return;
        }

        const auto describer = FromNode(node->Describer());
        const auto enumSource = new Enum(identifier, describer, node);

        ValidateDescriber(enumSource, describer, index, sourceFile);
        sourceFile->AddChild(enumSource->Name(), enumSource);
    }

    void CreateClass(const DataTypeNode* const node, SourceFile* const sourceFile)
    {
        const auto index = node->Index();
        const auto identifier = node->Name()->Value();

        if (sourceFile->GetChild(identifier) != nullptr)
        {
            PushException(new DuplicateStructureDefinitionException(index, sourceFile));
            return;
        }

        const auto describer = FromNode(node->Describer());
        const auto classSource = new ClassSource(identifier, describer, node);

        ValidateDescriber(classSource, describer, index, sourceFile);
        sourceFile->AddChild(classSource->Name(), classSource);
    }

    void CreateStruct(const DataTypeNode* const node, SourceFile* const sourceFile)
    {
        const auto index = node->Index();
        const auto identifier = node->Name()->Value();

        if (sourceFile->GetChild(identifier) != nullptr)
        {
            PushException(new DuplicateStructureDefinitionException(index, sourceFile));
            return;
        }

        const auto describer = FromNode(node->Describer());
        const auto structSource = new StructSource(identifier, describer, node);

        ValidateDescriber(structSource, describer, index, sourceFile);
        sourceFile->AddChild(structSource->Name(), structSource);
    }

    void ImportFile(const SourceFile* file, SourceFile* const sourceFile, const unsigned long index)
    {
        for (const auto type: file->values())
        {
            if (type->CheckDescriber(Describer::Public))
            {
                if (const auto tryRef = sourceFile->GetReference(type->Name()); tryRef == nullptr)
                    sourceFile->AddReference(type);
                else
                    PushException(new AmbiguousImportException(type->FullName(), tryRef->FullName(), index, sourceFile));
            }
        }
    }

    void ImportDirectory(const SourceDirectory* directory, SourceFile* const sourceFile, const unsigned long index)
    {
        for (const auto child: directory->values())
        {
            if (child->SourceType() == SourceType::File)
                ImportFile(dynamic_cast<const SourceFile*>(child), sourceFile, index);
        }
    }

    void ImportStatement(const ImportStatementNode* const statement, SourceFile* const sourceFile)
    {
        const auto path = statement->Path();
        const auto index = statement->Index();

        if (!std::regex_match(path, pathRegex))
        {
            PushException(new InvalidImportPathException(path, index, sourceFile));
            return;
        }

        auto current = sourceFile->Parent();
        std::vector<std::string> parsed;
        {
            std::istringstream iss(path);
            std::string identifier;

            while (std::getline(iss, identifier, delimiter))
                parsed.push_back(identifier);
        }

        if (parsed.empty())
            return;

        int i = parsed.at(0).empty();

        for (; i < parsed.size(); i++)
        {
            if (const auto& name = parsed.at(i); name.empty())
                current = current->Parent();
            else if (current->SourceType() == SourceType::Directory)
            {
                const auto casted = dynamic_cast<const SourceDirectory*>(current);
                current = casted->GetChild(name);

                if (current != nullptr)
                    continue;
            }

            break;
        }


        if (current == nullptr || i < parsed.size() - 2)
        {
            PushException(new InvalidImportPathException(path, index, sourceFile));
            return;
        }

        if (current->SourceType() == SourceType::Directory)
        {
            ImportDirectory(dynamic_cast<SourceDirectory*>(current), sourceFile, index);
            return;
        }
        if (current->SourceType() == SourceType::File)
        {
            if (i == parsed.size() - 1)
            {
                ImportFile(dynamic_cast<SourceFile*>(current), sourceFile, index);
                return;
            }
            if (i == parsed.size() - 2)
            {
                const auto file = dynamic_cast<SourceFile*>(current);
                const auto& identifier = parsed.at(i + 1);

                if (const auto type = file->GetChild(identifier); type != nullptr)
                {
                    sourceFile->AddReference(type);
                    return;
                }
            }
        }

        PushException(new InvalidImportPathException(path, index, sourceFile));
    }
}
