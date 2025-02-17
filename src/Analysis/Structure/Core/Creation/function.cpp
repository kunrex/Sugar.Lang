#include "function.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    Function::Function(const Enums::Describer describer, const DataType* creationType) : Describable(describer), Created(creationType), parameterTypes()
    { }

    bool Function::Readable() const { return true; }
    bool Function::Writable() const { return false; }

    const std::string& Function::ArgumentSignatureString() const
    {
        if (argumentSignature.empty())
        {
            argumentSignature += "(";
            for (int i = 0; i < parameterTypes.size(); i++)
            {
                argumentSignature += parameterTypes.at(i)->FullName();
                if (i != parameterTypes.size() - 1)
                    argumentSignature += " ";
            }

            argumentSignature += ")";
        }

        return argumentSignature;
    }

    int Function::ParameterCount() const { return parameterTypes.size(); }

    void Function::PushParameterType(const DataType* argument)
    {
        parameterTypes.push_back(argument);
    }

    const DataType* Function::ParameterAt(const int index) const
    {
        if (index > -1 && index < parameterTypes.size())
            return parameterTypes.at(index);

        return nullptr;
    }
}
