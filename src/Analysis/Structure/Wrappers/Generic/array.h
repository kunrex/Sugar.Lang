#ifndef ARRAY_H
#define ARRAY_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/DataTypes/generic_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Array final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Core::Interfaces::IBuiltInType
    {
        private:
            const IDataType* arrayType;

            explicit Array(const IDataType* arrayType);

        public:
            static const Array* Instance(const IDataType* dataType);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
