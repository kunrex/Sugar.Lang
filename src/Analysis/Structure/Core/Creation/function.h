#ifndef FUNCTION_H
#define FUNCTION_H

#include "../created.h"
#include "../describable.h"
#include "../Interfaces/i_read_write.h"
#include "../../Nodes/Global/global_node.h"

namespace Analysis::Structure::Core
{
    class Function : public Global::GlobalNode, public virtual Describable, public Created, public Interfaces::IReadWrite
    {
        protected:
            mutable std::string signature;
            mutable std::string argumentSignature;
            std::vector<const DataType*> parameterTypes;

            Function(Enums::Describer describer, const DataType* creationType);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] virtual const std::string& SignatureString() const = 0;
            [[nodiscard]] const std::string& ArgumentSignatureString() const;

            [[nodiscard]] int ParameterCount() const;
            void PushParameterType(const DataType* argument);
            [[nodiscard]] const DataType* ParameterAt(int index) const;
    };
}

#endif
