#ifndef ARRAY_H
#define ARRAY_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/generic_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Array final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            const DataType* arrayType;

            explicit Array(const DataType* arrayType);

        public:
            static const Array* Instance(const DataType* dataType);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
