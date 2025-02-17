#ifndef TUPLE_H
#define TUPLE_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"

namespace Analysis::Structure::Wrappers
{
    class Tuple final : public DataTypes::Class, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            std::vector<const DataType*> types;
            mutable std::string genericSignature;

            explicit Tuple();

        public:
            static const Tuple* Instance(const std::vector<const DataType*>& types);

            void InitialiseMembers() override;
            [[nodiscard]] const std::string& GenericSignature() const override;
    };
}

#endif
