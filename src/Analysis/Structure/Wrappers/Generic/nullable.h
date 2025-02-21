#ifndef NULLABLE_H
#define NULLABLE_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/generic_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Nullable final : public DataTypes::ValueType, public Services::SingletonCollection, public Core::GenericType, public Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            const DataType* nullableType;

            explicit Nullable(const DataType* nullableType);

        public:
            static const Nullable* Instance(const DataType* dataType);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
