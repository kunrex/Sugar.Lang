#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "../nameable.h"
#include "../describable.h"
#include "../Interfaces/DataTypes/i_data_type.h"

namespace Analysis::Structure::Core
{
    class DataType : public Nameable, public Describable, public virtual Interfaces::IDataType
    {
        protected:
            DataType(const std::string& name, Enums::Describer describer);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
