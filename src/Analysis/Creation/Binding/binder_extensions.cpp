#include "binder_extensions.h"

#include "../../../Exceptions/log_exception.h"
#include "../../../Exceptions/exception_manager.h"
#include "../../../Exceptions/Compilation/Analysis/type_exception.h"

#include "../../../Parsing/ParseNodes/Types/Created/created_type_node.h"
#include "../../../Parsing/ParseNodes/Types/BuiltIn/built_in_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/func_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/list_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/array_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/tuple_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/action_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/nullable_type_node.h"
#include "../../../Parsing/ParseNodes/Types/Keyword/Generic/dictionary_type_node.h"

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

using namespace Exceptions;

using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Types;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Creation::Binding
{
    void PushException(const LogException* const exception)
    {
        ExceptionManager::Instance().AddChild(exception);
    }

    const IDataType* BindBuiltInType(const BuiltInTypeNode* node)
    {
        switch (node->Kind())
        {
            case SyntaxKind::Short:
                return &Short::Instance();
            case SyntaxKind::Int:
                return &Integer::Instance();
            case SyntaxKind::Long:
                return &Long::Instance();
            case SyntaxKind::Float:
                return &Float::Instance();
            case SyntaxKind::Double:
                return &Double::Instance();
            case SyntaxKind::String:
                return &String::Instance();
            case SyntaxKind::Character:
                return &Character::Instance();
            case SyntaxKind::Boolean:
                return &Boolean::Instance();
            case SyntaxKind::Exception:
                return &Exception::Instance();
            case SyntaxKind::Math:
                return &Math::Instance();
            default:
                return &Object::Instance();
        }
    }

    const IDataType* BindArray(const ArrayTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();
        const auto typeNode = generic->GetChild(0);

        return Array::Instance(BindDataType(typeNode, source));
    }

    const IDataType* BindList(const ListTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();
        const auto typeNode = generic->GetChild(0);

        return List::Instance(BindDataType(typeNode, source));
    }

    const IDataType* BindDictionary(const DictionaryTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();

        const auto keyNode = generic->GetChild(0);
        const auto valueNode = generic->GetChild(1);

        return Dictionary::Instance(BindDataType(keyNode, source), BindDataType(valueNode, source));
    }

    const IDataType* BindNullable(const NullableTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();
        const auto typeNode = generic->GetChild(0);

        const auto type = BindDataType(typeNode, source);
        if (type->MemberType() != MemberType::ValueType)
            ExceptionManager::Instance().AddChild(new LogException("Only value types can be used in nullable<T>.", typeNode->Index(), source));

        return Nullable::Instance(type);
    }

    const IDataType* BindTuple(const TupleTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();

        std::vector<const IDataType*> types;
        for (const auto typeNode : *generic)
            types.push_back(BindDataType(typeNode, source));

        return Tuple::Instance(types);
    }

    const IDataType* BindAction(const ActionTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();

        std::vector<const IDataType*> types;
        for (const auto typeNode : *generic)
            types.push_back(BindDataType(typeNode, source));

        return Action::Instance(types);
    }

    const IDataType* BindFunc(const FuncTypeNode* const node, const SourceFile* const source)
    {
        const auto generic = node->Generic();

        std::vector<const IDataType*> types;
        for (const auto typeNode : *generic)
            types.push_back(BindDataType(typeNode, source));

        return Func::Instance(types);
    }

    const IDataType* BindDataType(const ParseNode* const node, const SourceFile* const source)
    {
        switch (node->NodeType())
        {
            case NodeType::BuiltInType:
                return BindBuiltInType(dynamic_cast<const BuiltInTypeNode*>(node));
            case NodeType::CreatedType:
                {
                    const auto casted = dynamic_cast<const CreatedTypeNode*>(node);
                    return source->GetReference(casted->Identifier()->Value());
                }
            case NodeType::FuncType:
                return BindFunc(dynamic_cast<const FuncTypeNode*>(node), source);
            case NodeType::ListType:
                return BindList(dynamic_cast<const ListTypeNode*>(node), source);
            case NodeType::TupleType:
                return BindTuple(dynamic_cast<const TupleTypeNode*>(node), source);
            case NodeType::ArrayType:
                return BindArray(dynamic_cast<const ArrayTypeNode*>(node), source);
            case NodeType::ActionType:
                return BindAction(dynamic_cast<const ActionTypeNode*>(node), source);
            case NodeType::NullableType:
                return BindNullable(dynamic_cast<const NullableTypeNode*>(node), source);
            case NodeType::DictionaryType:
                return BindDictionary(dynamic_cast<const DictionaryTypeNode*>(node), source);
            default:
                ExceptionManager::Instance().AddChild(new TypeNotFoundException(node->Index(), source));
                return &Object::Instance();
        }
    }
}
