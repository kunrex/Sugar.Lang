#include "project_binder.h"

#include <regex>
#include <sstream>

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compiling/Analysis/invalid_describer_exception.h"
#include "../../../Exceptions/Compiling/Analysis/ProjectBinding/ambiguous_import_exception.h"
#include "../../../Exceptions/Compiling/Analysis/ProjectBinding/duplicate_structure_definition_exception.h"
#include "../../../Exceptions/Compiling/Analysis/ProjectBinding/invalid_import_path_exception.h"


#include "../../Structure/Nodes/DataTypes/enum.h"
#include "../../Structure/Nodes/DataTypes/class.h"
#include "../../Structure/Nodes/DataTypes/struct.h"

using namespace Exceptions;

using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Statements;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;

constexpr char delimiter = '.';
const auto pathRegex = std::regex(R"(^(\.)*(?:[a-zA-Z0-9_-]+(?:\.[a-zA-Z0-9_-]+)*)?$)");

namespace Analysis::Creation
{
    void ValidateDescribable(const Core::Describable* const describable, Describer const describer, const SourceFile* const sourceFile)
    {
        if (!describable->ValidateDescriber(describer))
            ExceptionManager::Instance().AddChild(new InvalidDescriberException(describer, describer, sourceFile));
    }

    void CreateEnum(const DataTypeNode* const node, SourceFile* const sourceFile)
    {
        if (const auto identifier = node->Name()->Value(); sourceFile->Get(identifier) != nullptr)
        {
            ExceptionManager::Instance().AddChild(new DuplicateStructureDefinitionException(identifier, node->Index(), sourceFile));
            return;
        }

        const auto describer = FromNode(node->Describer());
        const auto enumSource = new Enum(describer, node);

        ValidateDescribable(enumSource, describer, sourceFile);
        sourceFile->Push(enumSource->Name(), enumSource);
    }

    void CreateClass(const DataTypeNode* const node, SourceFile* const sourceFile)
    {
        if (const auto identifier = node->Name()->Value(); sourceFile->Get(identifier) != nullptr)
        {
            ExceptionManager::Instance().AddChild(new DuplicateStructureDefinitionException(identifier, node->Index(), sourceFile));
            return;
        }

        const auto describer = FromNode(node->Describer());
        const auto classSource = new ClassSource(describer, node);

        ValidateDescribable(classSource, describer, sourceFile);
        sourceFile->Push(classSource->Name(), classSource);
    }

    void CreateStruct(const DataTypeNode* const node, SourceFile* const sourceFile)
    {
        if (const auto identifier = node->Name()->Value(); sourceFile->Get(identifier) != nullptr)
        {
            ExceptionManager::Instance().AddChild(new DuplicateStructureDefinitionException(identifier, node->Index(), sourceFile));
            return;
        }

        const auto describer = FromNode(node->Describer());
        const auto structSource = new StructSource(describer, node);

        ValidateDescribable(structSource, describer, sourceFile);
        sourceFile->Push(structSource->Name(), structSource);
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
                    ExceptionManager::Instance().AddChild(new AmbiguousImportException(type->FullName(), tryRef->FullName(), index, sourceFile));
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
        if (!std::regex_match(path, pathRegex))
        {
            ExceptionManager::Instance().AddChild(new InvalidImportPathException(path, statement->Index(), sourceFile));
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
                current = casted->Get(name);

                if (current != nullptr)
                    continue;
            }

            break;
        }


        if (current == nullptr || i < parsed.size() - 2)
        {
            ExceptionManager::Instance().AddChild(new InvalidImportPathException(path, statement->Index(), sourceFile));
            return;
        }

        if (current->SourceType() == SourceType::Directory)
        {
            ImportDirectory(dynamic_cast<SourceDirectory*>(current), sourceFile, statement->Index());
            return;
        }
        if (current->SourceType() == SourceType::File)
        {
            if (i == parsed.size() - 1)
            {
                ImportFile(dynamic_cast<SourceFile*>(current), sourceFile, statement->Index());
                return;
            }
            if (i == parsed.size() - 2)
            {
                const auto file = dynamic_cast<SourceFile*>(current);
                const auto& identifier = parsed.at(i + 1);

                if (const auto type = file->Get(identifier); type != nullptr)
                {
                    sourceFile->AddReference(type);
                    return;
                }
            }
        }

        ExceptionManager::Instance().AddChild(new InvalidImportPathException(path, statement->Index(), sourceFile));
    }
}
