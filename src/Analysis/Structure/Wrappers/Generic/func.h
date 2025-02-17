#ifndef FUNC_H
#define FUNC_H

#include "../../Nodes/DataTypes/class.h"
#include "../../../../Services/singleton_service.h"
#include "../../Core/Interfaces/i_built_in_type.h"
#include "../../Core/Interfaces/i_generic_class.h"
#include "../../Nodes/Global/UserDefined/method_function.h"

namespace Analysis::Structure::Wrappers
{
    class Func final : public DataTypes::Class, public Services::SingletonCollection, public Analysis::Core::Interfaces::IBuiltInType, public Core::Interfaces::IGenericClass
    {
        private:
            std::vector<const DataType*> types;

            mutable std::string genericSignature;
            mutable std::string callSignature;

            Func();

        public:
            static const Func* Instance(const std::vector<const DataType*>& types);

            [[nodiscard]] const std::string& GenericSignature() const override;
            [[nodiscard]] const std::string& CallSignature() const;
            void InitialiseMembers() override;
    };
}

#endif
