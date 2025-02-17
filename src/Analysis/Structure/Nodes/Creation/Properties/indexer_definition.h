#ifndef INDEXER_DEFINITION_H
#define INDEXER_DEFINITION_H

#include "../../../Core/created.h"
#include "../../../Core/describable.h"
#include "../../Global/global_node.h"
#include "../../../Core/Interfaces/i_read_write.h"

namespace Analysis::Structure::Creation
{
    class IndexerDefinition : public Global::GlobalNode, public Core::Describable, public Core::Created, public Core::Interfaces::IReadWrite
    {
        protected:
            mutable std::string getSignature;
            mutable std::string setSignature;

            explicit IndexerDefinition(Enums::Describer describer, const Core::DataType* creationType);

        public:
            [[nodiscard]] virtual const std::string& SignatureGetString() const = 0;
            [[nodiscard]] virtual const std::string& SignatureSetString() const = 0;

            [[nodiscard]] virtual int ParameterCount() const = 0;
            [[nodiscard]] virtual const Core::DataType* ParameterAt(int index) const = 0;
    };
}

#endif
