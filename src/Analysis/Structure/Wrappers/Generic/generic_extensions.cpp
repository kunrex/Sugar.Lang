#include "generic_extensions.h"

namespace Analysis::Structure::Wrappers
{
    std::string MapGenericSignature(const std::vector<const Core::DataType*>& types)
    {
        std::string signature;
        for (int i = 0; i < types.size(); i++)
        {
            signature += types.at(i)->FullName();
            if (i != types.size() - 1)
                signature += ", ";
        }

        return signature;
    }
}
