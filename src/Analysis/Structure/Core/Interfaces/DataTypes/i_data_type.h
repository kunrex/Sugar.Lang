#ifndef I_DATA_TYPE_H
#define I_DATA_TYPE_H

#include "../i_node.h"
#include "../i_nameable.h"
#include "../i_slot_size.h"
#include "../i_describable.h"
#include "../Creation/i_function.h"
#include "../Creation/i_characteristic.h"
#include "../Creation/i_operator_overload.h"
#include "../Creation/i_indexer_definition.h"
#include "../Creation/i_function_definition.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IDataType : public virtual INode, public virtual INameable, public virtual IFullyNameable, public virtual IDescribable, public virtual ISlotSize
    {
        public:
            virtual void PushCharacteristic(ICharacteristic* characteristic) = 0;
            [[nodiscard]] virtual const ICharacteristic* FindCharacteristic(const std::string& name) const = 0;

            virtual void PushFunction(IFunctionDefinition* function) = 0;
            [[nodiscard]] virtual const IFunctionDefinition* FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const = 0;

            virtual void PushConstructor(IFunction* constructor) = 0;
            [[nodiscard]] virtual const IFunction* FindConstructor(const std::vector<const IDataType*>& argumentList) const = 0;

            virtual void PushIndexer(IIndexerDefinition* indexer) = 0;
            [[nodiscard]] virtual const IIndexerDefinition* FindIndexer(const std::vector<const IDataType*>& argumentList) const = 0;

            virtual void PushImplicitCast(IFunction* cast) = 0;
            [[nodiscard]] virtual const IFunction* FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const = 0;
            virtual void PushExplicitCast(IFunction* cast) = 0;
            [[nodiscard]] virtual const IFunction* FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const = 0;

            virtual void PushOverload(IOperatorOverload* overload) = 0;
            [[nodiscard]] virtual const IOperatorOverload* FindOverload(Tokens::Enums::SyntaxKind base) const = 0;
    };
}

#endif
