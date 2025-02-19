#ifndef INDEXER_DEFINITION_H
#define INDEXER_DEFINITION_H

#include "../../Core/created.h"
#include "../../Core/describable.h"
#include "../../Core/Interfaces/i_function.h"
#include "../../Core/Interfaces/i_property.h"
#include "../../Core/Interfaces/i_read_write.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Creation
{
    class IndexerDefinition : public Global::GlobalNode, public Core::Describable, public Core::Created, public Core::Interfaces::IFunction, public Core::Interfaces::IProperty, public Core::Interfaces::IReadWrite
    {
        protected:
            mutable std::string getSignature;
            mutable std::string setSignature;

            IndexerDefinition(Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
