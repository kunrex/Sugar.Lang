#ifndef LIST_H
#define LIST_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/generic_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class List final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            const DataType* listType;

            explicit List(const DataType* listType);

        public:
            static const List* Instance(const DataType* dataType);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
