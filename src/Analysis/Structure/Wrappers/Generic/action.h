#ifndef ACTION_H
#define ACTION_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/generic_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Action final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            mutable std::string callSignature;

            std::vector<const DataType*> types;

            Action();

        public:
            static const Action* Instance(const std::vector<const DataType*>& types);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;

            [[nodiscard]] unsigned long TypeCount() const;
            [[nodiscard]] const DataType* TypeAt(unsigned long index) const;
    };
}

#endif