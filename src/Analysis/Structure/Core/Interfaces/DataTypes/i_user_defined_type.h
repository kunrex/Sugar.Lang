#ifndef I_USER_DEFINED_TYPE_H
#define I_USER_DEFINED_TYPE_H

#include "i_data_type.h"

#include "../../../source_file.h"
#include "../../../Global/Functions/constructor.h"
#include "../Creation/i_constructor.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IUserDefinedType : public Services::Child<SourceFile>, public virtual IDataType, public Services::Printable, public virtual ITranspilable
    {
        public:
            virtual void PushCharacteristic(ICharacteristic* characteristic) = 0;

            virtual void PushFunction(IFunctionDefinition* function) = 0;

            [[nodiscard]] virtual IConstructor* StaticConstructor() const = 0;
            [[nodiscard]] virtual IConstructor* InstanceConstructor() const = 0;

            virtual void PushConstructor(IConstructor* constructor) = 0;

            virtual void PushIndexer(IIndexerDefinition* indexer) = 0;

            virtual void PushImplicitCast(IFunction* cast) = 0;
            virtual void PushExplicitCast(IFunction* cast) = 0;

            virtual void PushOverload(IOperatorOverload* overload) = 0;
    };
}

#endif
