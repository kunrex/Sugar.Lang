#ifndef I_USER_DEFINED_TYPE_H
#define I_USER_DEFINED_TYPE_H

#include "i_data_type.h"

#include "../../../source_file.h"

#include "../../Creation/characteristic.h"
#include "../../../Global/Properties/indexer.h"

#include "../Scoped/i_scoped.h"

#include "../../../../../Parsing/ParseNodes/DataTypes/data_type_node.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IUserDefinedType : public Services::Child<SourceFile>, public virtual IDataType
    {
        public:
            [[nodiscard]] virtual const ParseNodes::DataTypes::DataTypeNode* Skeleton() const = 0;

            [[nodiscard]] virtual IScoped* StaticConstructor() const = 0;
            [[nodiscard]] virtual IScoped* InstanceConstructor() const = 0;

            virtual void PushCharacteristic(ICharacteristic* characteristic) = 0;

            virtual void PushFunction(IFunctionDefinition* function) = 0;

            virtual void PushConstructor(IFunction* constructor) = 0;

            virtual void PushIndexer(IIndexerDefinition* indexer) = 0;

            virtual void PushImplicitCast(IFunction* cast) = 0;
            virtual void PushExplicitCast(IFunction* cast) = 0;

            virtual void PushOverload(IOperatorOverload* overload) = 0;

            [[nodiscard]] virtual std::vector<const ICharacteristic*> AllCharacteristics() const = 0;
            [[nodiscard]] virtual std::vector<IScoped*> AllScoped() const = 0 ;
    };
}

#endif
