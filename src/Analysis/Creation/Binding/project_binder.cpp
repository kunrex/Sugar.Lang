#include "project_binder.h"

#include <regex>
#include <sstream>

#include "binder_extensions.h"

#include "../../Structure/source_directory.h"

#include "../../Structure/DataTypes/enum.h"
#include "../../Structure/DataTypes/class.h"
#include "../../Structure/DataTypes/value_type.h"

#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Project/ambiguous_import_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Project/invalid_import_path_exception.h"
#include "../../../Exceptions/Compilation/Analysis/Project/duplicate_structure_definition_exception.h"

using namespace Exceptions;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;

constexpr char delimiter = '.';
const auto pathRegex = std::regex(R"(^(\.)*(?:[a-zA-Z0-9_-]+(?:\.[a-zA-Z0-9_-]+)*)?$)");

namespace Analysis::Creation::Binding
{
    void CreateEnum(const IParseNode* const node, SourceFile* const sourceFile)
    {
        const auto index = node->Token().Index();
        const auto identifier = *node->GetChild(static_cast<int>(ChildCode::Identifier))->Token().Value<std::string>();

        if (sourceFile->GetChild(identifier) != nullptr)
        {
            ExceptionManager::PushException(DuplicateStructureDefinitionException(index, sourceFile));
            return;
        }

        const auto describer = FromNode(node->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto enumSource = new Enum(identifier, describer == Describer::None ? Describer::Public : describer, node->GetChild(static_cast<int>(ChildCode::Body)));

        ValidateDescriber(enumSource, Describer::AccessModifiers | Describer::Static, node, enumSource);
        sourceFile->AddChild(identifier, enumSource);
    }

    void CreateClass(const IParseNode* const node, SourceFile* const sourceFile)
    {
        const auto index = node->Token().Index();
        const auto identifier = *node->GetChild(static_cast<int>(ChildCode::Identifier))->Token().Value<std::string>();

        if (sourceFile->GetChild(identifier) != nullptr)
        {
            ExceptionManager::PushException(DuplicateStructureDefinitionException(index, sourceFile));
            return;
        }

        const auto describer = FromNode(node->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto classSource = new ClassSource(identifier, describer == Describer::None ? Describer::Public : describer, node->GetChild(static_cast<int>(ChildCode::Body)));

        ValidateDescriber(classSource, Describer::Static | Describer::AccessModifiers, node, classSource);
        sourceFile->AddChild(identifier, classSource);
    }

    void CreateStruct(const IParseNode* const node, SourceFile* const sourceFile)
    {
        const auto index = node->Token().Index();
        const auto identifier = *node->GetChild(static_cast<int>(ChildCode::Identifier))->Token().Value<std::string>();

        if (sourceFile->GetChild(identifier) != nullptr)
        {
            ExceptionManager::PushException(DuplicateStructureDefinitionException(index, sourceFile));
            return;
        }

        const auto describer = FromNode(node->GetChild(static_cast<int>(ChildCode::Describer)));
        const auto structSource = new StructSource(identifier, describer == Describer::None ? Describer::Public : describer, node->GetChild(static_cast<int>(ChildCode::Body)));

        ValidateDescriber(structSource, Describer::AccessModifiers, node, structSource);
        sourceFile->AddChild(identifier, structSource);
    }

    void ImportFile(const SourceFile* const file, SourceFile* const sourceFile, const unsigned long index)
    {
        for (const auto type: file->values())
        {
            if (type->CheckDescriber(Describer::Public))
            {
                if (const auto tryRef = sourceFile->GetReference(type->Name()); tryRef == nullptr)
                    sourceFile->AddReference(type);
                else
                    ExceptionManager::PushException(AmbiguousImportException(type->FullName(), tryRef->FullName(), index, sourceFile));
            }
        }
    }

    void ImportDirectory(const SourceDirectory* const directory, SourceFile* const sourceFile, const unsigned long index)
    {
        for (const auto child: directory->values())
        {
            if (child->SourceType() == SourceType::File)
                ImportFile(dynamic_cast<const SourceFile*>(child), sourceFile, index);
        }
    }

    void ImportStatement(const IParseNode* const statement, SourceFile* const sourceFile)
    {
        const auto path = *statement->Token().Value<std::string>();
        const auto index = statement->Token().Index();

        if (!std::regex_match(path, pathRegex))
        {
            ExceptionManager::PushException(InvalidImportPathException(path, index, sourceFile));
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
            {
                current = current->Parent();
                continue;
            }
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
            ExceptionManager::PushException(InvalidImportPathException(path, index, sourceFile));
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

        ExceptionManager::PushException(InvalidImportPathException(path, index, sourceFile));
    }
}
