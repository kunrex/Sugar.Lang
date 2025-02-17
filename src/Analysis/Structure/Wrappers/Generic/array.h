#ifndef ARRAY_H
#define ARRAY_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"

namespace Analysis::Structure::Wrappers
{
    class Array final : public DataTypes::Class, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            const DataType* arrayType;
            mutable std::string genericSignature;

            explicit Array(const DataType* arrayType);

        public:
            static const Array* Instance(const DataType* dataType);

            [[nodiscard]] const std::string& GenericSignature() const override;
            void InitialiseMembers() override;
    };
}

#endif
