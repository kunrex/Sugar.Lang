#ifndef ENUM_H
#define ENUM_H

#include <map>

#include "../../Core/DataTypes/data_type.h"
#include "../../Core/DataTypes/user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class Enum final : public Core::DataType, public Core::UserDefinedType
    {
        protected:
            std::map<std::string, std::tuple<int, Core::Characteristic>> characteristics;

        public:
            Enum(Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] int SlotCount() const override;

            void PushCharacteristic(Core::Characteristic* characteristic) override;

            void PushFunction(Creation::FunctionDefinition* function) override;

            void PushIndexer(Creation::IndexerDefinition* indexer) override;

            void PushImplicitCast(Creation::CastDefinition* cast) override;
            void PushExplicitCast(Creation::CastDefinition* cast) override;
            void PushOverload(Creation::OverloadDefinition* overload) override;

            void PushDestructor(Creation::DestructorDefinition* destructor) override;
    };
}

#endif
