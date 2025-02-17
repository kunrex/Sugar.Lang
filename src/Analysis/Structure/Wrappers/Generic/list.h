#ifndef LIST_H
#define LIST_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"

namespace Analysis::Structure::Wrappers
{
    class List final : public DataTypes::Class, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            const DataType* listType;
            mutable std::string genericSignature;

            explicit List(const DataType* listType);

        public:
            static const List* Instance(const DataType* dataType);

            [[nodiscard]] const std::string& GenericSignature() const override;
            void InitialiseMembers() override;
    };
}

#endif
