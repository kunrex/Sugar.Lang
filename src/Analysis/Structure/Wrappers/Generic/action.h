#ifndef ACTION_H
#define ACTION_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/DataTypes/generic_type.h"
#include "../../Core/Interfaces/DataTypes/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Action final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Core::Interfaces::IBuiltInType
    {
        private:
            mutable std::string callSignature;

            std::vector<const IDataType*> types;

            Action();

        public:
            static const Action* Instance(const std::vector<const IDataType*>& types);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;
    };
}

#endif