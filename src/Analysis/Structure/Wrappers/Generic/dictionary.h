#ifndef DICTIONARY_WRAPPER_H
#define DICTIONARY_WRAPPER_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"

namespace Analysis::Structure::Wrappers
{
    class Dictionary final : public DataTypes::Class, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            const DataType* keyType;
            const DataType* valueType;
            mutable std::string genericSignature;

            explicit Dictionary(const DataType* keyType, const DataType* valueType);

        public:
            static const Dictionary* Instance(const DataType* keyType, const DataType* valueType);

            [[nodiscard]] const std::string& GenericSignature() const override;
            void InitialiseMembers() override;
    };
}

#endif
