#ifndef FUNCTION_H
#define FUNCTION_H

#include "../../Nodes/Global/global_node.h"
#include "../../../../Services/collection.h"
#include "../../Nodes/Creation/Variables/variable.h"

namespace Analysis::Structure::Core
{
    class Function : public Global::GlobalNode, public Describable, public Created, public Services::ConstantCollection<Creation::Variable>, public Interfaces::IReadWrite
    {
        protected:
            Function(Enums::Describer describer, const DataType* creationType);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string SignatureString() const;

            bool operator<(const Function& rhs) const;
    };
}

#endif
