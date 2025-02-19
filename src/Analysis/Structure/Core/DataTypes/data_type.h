#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "../nameable.h"
#include "../describable.h"
#include "../Interfaces/i_node.h"
#include "../Interfaces/i_slot_size.h"
#include "../Creation/characteristic.h"

#include "../../source_file.h"

#include "../../Creation/Functions/cast_definition.h"
#include "../../Creation/Functions/overload_definition.h"
#include "../../Creation/Properties/indexer_definition.h"
#include "../../Creation/Functions/function_definition.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Core
{
    class DataType : public virtual Interfaces::INode, public Nameable, public Describable, public Services::ConstantChild<SourceFile>, public Interfaces::ISlotSize
    {
        protected:
            DataType(const std::string& name, Enums::Describer describer);

        public:
            virtual void PushCharacteristic(Characteristic* characteristic) = 0;
            [[nodiscard]] virtual const Characteristic* FindCharacteristic(const std::string& name) const = 0;

            virtual void PushFunction(Creation::FunctionDefinition* function) = 0;
            [[nodiscard]] virtual const Creation::FunctionDefinition* FindFunction(const std::string& name, const std::vector<const DataType*>& argumentList) const = 0;

            virtual void PushConstructor(Creation::ConstructorDefinition* constructor) = 0;
            [[nodiscard]] virtual const Creation::ConstructorDefinition* FindConstructor(const std::vector<const DataType*>& argumentList) const = 0;

            virtual void PushIndexer(Creation::IndexerDefinition* indexer) = 0;
            [[nodiscard]] virtual const Creation::IndexerDefinition* FindIndexer(const std::vector<const DataType*>& argumentList) const = 0;

            virtual void PushImplicitCast(Creation::CastDefinition* cast) = 0;
            [[nodiscard]] virtual const Creation::CastDefinition* FindImplicitCast(const DataType* returnType, const DataType* fromType) const = 0;
            virtual void PushExplicitCast(Creation::CastDefinition* cast) = 0;
            [[nodiscard]] virtual const Creation::CastDefinition* FindExplicitCast(const DataType* returnType, const DataType* fromType) const = 0;

            virtual void PushOverload(Creation::OverloadDefinition* overload) = 0;
            [[nodiscard]] virtual const Creation::OverloadDefinition* FindOverload(Tokens::Enums::SyntaxKind base) const = 0;

            [[nodiscard]] virtual std::vector<const Characteristic*> AllCharacteristics() const = 0;
    };
}

#endif
