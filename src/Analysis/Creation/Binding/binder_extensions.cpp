#include "binder_extensions.h"

#include "../../Structure/Wrappers/Value/long.h"
#include "../../Structure/Wrappers/Value/short.h"
#include "../../Structure/Wrappers/Value/integer.h"

#include "../../Structure/Wrappers/Value/float.h"
#include "../../Structure/Wrappers/Value/double.h"

#include "../../Structure/Wrappers/Value/boolean.h"
#include "../../Structure/Wrappers/Value/character.h"

#include "../../Structure/Wrappers/Reference/math.h"
#include "../../Structure/Wrappers/Reference/string.h"
#include "../../Structure/Wrappers/Reference/object.h"
#include "../../Structure/Wrappers/Reference/exception.h"

#include "../../Structure/Wrappers/Generic/func.h"
#include "../../Structure/Wrappers/Generic/list.h"
#include "../../Structure/Wrappers/Generic/array.h"
#include "../../Structure/Wrappers/Generic/tuple.h"
#include "../../Structure/Wrappers/Generic/action.h"
#include "../../Structure/Wrappers/Generic/nullable.h"
#include "../../Structure/Wrappers/Generic/dictionary.h"

#include "../../../Exceptions/log_exception.h"
#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/type_exception.h"
#include "../../../Exceptions/Compilation/Analysis/invalid_describer_exception.h"

#include "../../../Parsing/ParseNodes/Types/BuiltIn/built_in_type_node.h"

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Creation::Binding
{

    void ValidateDescriber(const Describable* const describable, const Describer allowed, const IParseNode* const parseNode, const IUserDefinedType* const dataType)
    {
        if (!describable->ValidateDescriber(allowed))
            ExceptionManager::PushException(InvalidDescriberException(describable->Describer(), allowed, parseNode, dataType));
    }

    const IDataType* BindBuiltInType(const IParseNode* const node)
    {
        switch (node->Token().Kind())
        {
            case SyntaxKind::Short:
                return Short::Instance();
            case SyntaxKind::Int:
                return Integer::Instance();
            case SyntaxKind::Long:
                return Long::Instance();
            case SyntaxKind::Float:
                return Float::Instance();
            case SyntaxKind::Double:
                return Double::Instance();
            case SyntaxKind::String:
                return String::Instance();
            case SyntaxKind::Character:
                return Character::Instance();
            case SyntaxKind::Boolean:
                return Boolean::Instance();
            case SyntaxKind::Exception:
                return Exception::Instance();
            case SyntaxKind::Math:
                return Math::Instance();
            default:
                return Object::Instance();
        }
    }

    const IDataType* BindArray(const IParseNode* const node, const SourceFile* const source)
    {
        return Array::Instance(BindDataType(node->GetChild(0), source));
    }

    const IDataType* BindList(const IParseNode* const node, const SourceFile* const source)
    {
        return List::Instance(BindDataType(node->GetChild(0), source));
    }

    const IDataType* BindDictionary(const IParseNode* const node, const SourceFile* const source)
    {
        return Dictionary::Instance(BindDataType(node->GetChild(0), source), BindDataType(node->GetChild(1), source));
    }

    const IDataType* BindNullable(const IParseNode* const node, const SourceFile* const source)
    {
        const auto typeNode = node->GetChild(0);
        const auto type = BindDataType(typeNode, source);
        if (type->MemberType() != MemberType::ValueType)
            ExceptionManager::PushException(LogException("Only value types can be used in nullable<T>.", typeNode->Token().Index(), source));

        return Nullable::Instance(type);
    }

    const IDataType* BindTuple(const IParseNode* const node, const SourceFile* const source)
    {
        std::vector<const IDataType*> types;
        types.reserve(node->ChildCount());

        for (auto i = 0; i < node->ChildCount(); i++)
            types.push_back(BindDataType(node->GetChild(i), source));

        return Tuple::Instance(types);
    }

    const IDataType* BindAction(const IParseNode* const node, const SourceFile* const source)
    {
        std::vector<const IDataType*> types;
        types.reserve(node->ChildCount());

        for (auto i = 0; i < node->ChildCount(); i++)
            types.push_back(BindDataType(node->GetChild(i), source));

        return Action::Instance(types);
    }

    const IDataType* BindFunc(const IParseNode* const node, const SourceFile* const source)
    {
        std::vector<const IDataType*> types;
        types.reserve(node->ChildCount());

        for (auto i = 0; i < node->ChildCount(); i++)
            types.push_back(BindDataType(node->GetChild(i), source));

        return Func::Instance(types);
    }

    const IDataType* BindDataType(const IParseNode* const node, const SourceFile* const source)
    {
        switch (node->NodeType())
        {
            case NodeType::BuiltInType:
                return BindBuiltInType(node);
            case NodeType::CreatedType:
                {
                    if (const auto type = source->GetReference(*node->Token().Value<std::string>()); type != nullptr)
                        return type;
                }
                break;
            case NodeType::FuncType:
                return BindFunc(node, source);
            case NodeType::ListType:
                return BindList(node, source);
            case NodeType::TupleType:
                return BindTuple(node, source);
            case NodeType::ArrayType:
                return BindArray(node, source);
            case NodeType::ActionType:
                return BindAction(node, source);
            case NodeType::NullableType:
                return BindNullable(node, source);
            case NodeType::DictionaryType:
                return BindDictionary(node, source);
            default:
               break;
        }

        ExceptionManager::PushException(TypeNotFoundException(node, source));
        return Object::Instance();
    }
}
