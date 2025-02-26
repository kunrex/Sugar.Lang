#ifndef NULLABLE_H
#define NULLABLE_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/value_type.h"
#include "../../Core/DataTypes/generic_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Nullable final : public DataTypes::ValueType, public Services::SingletonCollection, public Core::GenericType, public virtual Core::Interfaces::IBuiltInType
    {
        private:
            const IDataType* nullableType;

            explicit Nullable(const DataType* nullableType);

        public:
            static const Nullable* Instance(const IDataType* dataType);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
