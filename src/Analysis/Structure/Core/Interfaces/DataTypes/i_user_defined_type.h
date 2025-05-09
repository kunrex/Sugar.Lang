#ifndef I_USER_DEFINED_TYPE_H
#define I_USER_DEFINED_TYPE_H

#include "i_data_type.h"

#include "../../../source_file.h"

#include "../Scoped/i_scoped.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IUserDefinedType : public Services::Child<SourceFile>, public virtual IDataType, public Services::Printable
    {
        public:
            [[nodiscard]] virtual const ParseNodes::Core::Interfaces::IParseNode* Skeleton() const = 0;

            [[nodiscard]] virtual unsigned long ConstructorCount() const = 0;

            virtual void PushCharacteristic(ICharacteristic* characteristic) = 0;

            virtual void PushFunction(IFunctionDefinition* function) = 0;

            virtual void PushConstructor(IFunction* constructor) = 0;

            virtual void PushIndexer(IIndexerDefinition* indexer) = 0;

            virtual void PushImplicitCast(IFunction* cast) = 0;
            virtual void PushExplicitCast(IFunction* cast) = 0;

            virtual void PushOverload(IOperatorOverload* overload) = 0;

            [[nodiscard]] virtual std::vector<ICharacteristic*> AllCharacteristics() const = 0;
            [[nodiscard]] virtual std::vector<IScoped*> AllScoped() const = 0;
    };
}

#endif
