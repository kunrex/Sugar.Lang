#ifndef VARIABLE_H
#define VARIABLE_H

#include "../../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Creation
{
    class Variable : public Core::Characteristic
    {
        public:
            Variable(const std::string& name, Enums::Describer describer, const Core::DataType* creationType);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
