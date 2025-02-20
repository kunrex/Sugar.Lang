#ifndef TUPLE_H
#define TUPLE_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/generic_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Tuple final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            mutable std::string callSignature;

            std::vector<const DataType*> types;

            explicit Tuple();

        public:
            static const Tuple* Instance(const std::vector<const DataType*>& types);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif
