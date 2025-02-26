#ifndef DICTIONARY_WRAPPER_H
#define DICTIONARY_WRAPPER_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/DataTypes/generic_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Dictionary final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Core::Interfaces::IBuiltInType
    {
        private:
            const IDataType* keyType;
            const IDataType* valueType;

            explicit Dictionary(const IDataType* keyType, const IDataType* valueType);

        public:
            static const Dictionary* Instance(const IDataType* keyType, const IDataType* valueType);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
