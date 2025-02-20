#ifndef DICTIONARY_WRAPPER_H
#define DICTIONARY_WRAPPER_H

#include "../../../../Services/singleton_service.h"
#include "../../Core/generic_type.h"

#include "../../DataTypes/class.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Dictionary final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, virtual public Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            const DataType* keyType;
            const DataType* valueType;

            explicit Dictionary(const DataType* keyType, const DataType* valueType);

        public:
            static const Dictionary* Instance(const DataType* keyType, const DataType* valueType);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
