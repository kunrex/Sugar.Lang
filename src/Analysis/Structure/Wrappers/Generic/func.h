#ifndef FUNC_H
#define FUNC_H

#include "../../../../Services/singleton_service.h"

#include "../../DataTypes/class.h"
#include "../../Core/generic_type.h"
#include "../../Core/Interfaces/i_built_in_type.h"

namespace Analysis::Structure::Wrappers
{
    class Func final : public DataTypes::Class, public Services::SingletonCollection, public Core::GenericType, public virtual Analysis::Core::Interfaces::IBuiltInType
    {
        private:
            mutable std::string callSignature;

            std::vector<const DataType*> types;

            Func();

        public:
            static const Func* Instance(const std::vector<const DataType*>& types);

            [[nodiscard]] const std::string& FullName() const override;

            void InitialiseMembers() override;

            [[nodiscard]] unsigned long TypeCount() const;
            [[nodiscard]] const DataType* TypeAt(unsigned long index) const;
    };
}

#endif
