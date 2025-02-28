#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "../nameable.h"
#include "../describable.h"
#include "../Interfaces/DataTypes/i_data_type.h"

#include "../../source_file.h"

namespace Analysis::Structure::Core
{
    class DataType : public Services::ConstantChild<SourceFile>, public Nameable, public Describable, public virtual Interfaces::IDataType
    {
        protected:
            DataType(const std::string& name, Enums::Describer describer);
    };
}

#endif
