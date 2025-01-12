#include "function.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    Function::Function(const Enums::Describer describer, const DataType* creationType) : Describable(describer), Created(creationType)
    { }

    bool Function::Readable() const { return true; }
    bool Function::Writable() const { return false; }

    std::string Function::SignatureString() const
    {
        string signature = "(";

        for (int i = 0; i < ChildCount(); i++)
        {
            signature += GetChild(i)->CreationType()->FullName();
            if (i < ChildCount() - 1)
                signature += " ";
        }

        return signature + ")";
    }

    bool Function::operator<(const Function& rhs) const
    {
        for (int i = 0; i < std::min(children.size(), rhs.children.size()); i++)
            if (children[i]->Name() != rhs.children[i]->Name())
                return children[i]->Name() < rhs.children[i]->Name();

        return false;
    }

}
