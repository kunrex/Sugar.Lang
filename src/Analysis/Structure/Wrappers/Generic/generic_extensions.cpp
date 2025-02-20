#include "generic_extensions.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

namespace Analysis::Structure::Wrappers
{
    string MapGenericSignature(const std::vector<const Core::DataType*>& types)
    {
        std::string signature;
        for (int i = 0; i < types.size(); i++)
        {
            signature += types.at(i)->FullName();
            if (i < types.size() - 1)
                signature += ", ";
        }

        return signature;
    }

    string MapGenericCallSignature(const std::vector<const Core::DataType*>& types)
    {
        std::string signature;
        for (int i = 0; i < types.size(); i++)
        {
            signature += "!" + i;
            if (i < types.size() - 1)
                signature += ", ";
        }

        return signature;
    }
}
