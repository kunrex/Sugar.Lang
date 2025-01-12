#ifndef CLASS_H
#define CLASS_H

#include <map>
#include <set>

#include "../../Core/DataTypes/data_type.h"
#include "../../Core/DataTypes/user_defined_type.h"

namespace Analysis::Structure::DataTypes
{
    class Class : public Core::DataType
    {
        protected:
            std::map<std::string, Core::Characteristic*> characteristics;

            std::set<Creation::FunctionDefinition*> functions;

            std::set<Creation::IndexerDefinition*> indexers;

            std::set<std::string, Creation::CastDefinition*> implicitCasts;
            std::set<std::string, Creation::CastDefinition*> explicitCasts;

            std::set<std::string, Creation::OverloadDefinition*> overloads;

            Creation::DestructorDefinition* destructor;

        public:
            Class(const std::string& name, Enums::Describer describer);

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

     class ClassSource final : public Class, public Core::UserDefinedType
     {
        public:
            ClassSource(const std::string& name, Enums::Describer describer, const ParseNodes::DataTypes::DataTypeNode* skeleton);
     };
}

#endif
