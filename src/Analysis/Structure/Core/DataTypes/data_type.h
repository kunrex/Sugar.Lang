#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "../nameable.h"
#include "../describable.h"
#include "../../source_file.h"
#include "../Interfaces/i_node.h"
#include "../Interfaces/i_slot_size.h"
#include "../Creation/characteristic.h"
#include "../../Nodes/Creation/Functions/cast_definition.h"
#include "../../Nodes/Creation/Functions/overload_definition.h"
#include "../../Nodes/Creation/Properties/indexer_definition.h"
#include "../../Nodes/Creation/Functions/function_definition.h"
#include "../../Nodes/Creation/Functions/destructor_definition.h"

namespace Analysis::Structure::Core
{
    class DataType : public Interfaces::INode, public Services::Child<SourceFile>, public Nameable, public Describable, public Interfaces::ISlotSize
    {
        protected:
            DataType(const std::string& name, Enums::Describer describer);

        public:
            void SetParent(const SourceFile* parent) override;

            virtual void PushCharacteristic(Characteristic* characteristic) = 0;

            virtual void PushFunction(Creation::FunctionDefinition* function) = 0;

            virtual void PushIndexer(Creation::IndexerDefinition* indexer) = 0;

            virtual void PushImplicitCast(Creation::CastDefinition* cast) = 0;
            virtual void PushExplicitCast(Creation::CastDefinition* cast) = 0;

            virtual void PushOverload(Creation::OverloadDefinition* overload) = 0;

            virtual void PushDestructor(Creation::DestructorDefinition* destructor) = 0;
    };
}

#endif
