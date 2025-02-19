#ifndef NULLABLE_H
#define NULLABLE_H

#include "../../Nodes/DataTypes/struct.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"

namespace Analysis::Structure::Wrappers
{
    class Nullable final : public DataTypes::Struct, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            const DataType* nullableType;
            mutable std::string genericSignature;

            explicit Nullable(const DataType* nullableType);

        public:
            static const Nullable* Instance(const DataType* dataType);

            [[nodiscard]] const std::string& GenericSignature() const override;
            void InitialiseMembers() override;
    };
}

#endif
