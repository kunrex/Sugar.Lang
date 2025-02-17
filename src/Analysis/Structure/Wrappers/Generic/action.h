#ifndef ACTION_H
#define ACTION_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"

namespace Analysis::Structure::Wrappers
{
    class Action : public DataTypes::Class, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            std::vector<const DataType*> types;

            mutable std::string genericSignature;
            mutable std::string callSignature;

            Action();

        public:
            static const Action* Instance(const std::vector<const DataType*>& types);

            [[nodiscard]] const std::string& GenericSignature() const override;
            [[nodiscard]] const std::string& CallSignature() const;
            void InitialiseMembers() override;

            [[nodiscard]] int TypeCount() const;
            [[nodiscard]] const DataType* TypeAt(int index) const;
    };
}

#endif