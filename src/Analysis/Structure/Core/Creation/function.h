#ifndef FUNCTION_H
#define FUNCTION_H

#include "../created.h"
#include "../describable.h"
#include "../Interfaces/i_function.h"
#include "../Interfaces/i_read_write.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Core
{
    class Function : public Global::GlobalNode, public virtual Describable, public virtual Created, public Interfaces::IFunction, public Interfaces::IReadWrite
    {
        protected:
            mutable std::string signature;
            mutable std::string argumentSignature;

            Function(Enums::Describer describer, const DataType* creationType);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] virtual const std::string& SignatureString() const = 0;
            [[nodiscard]] virtual const std::string& ArgumentSignatureString() const = 0;
    };
}

#endif
