#include "characteristic.h"

using namespace std;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Characteristic::Characteristic(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const parseNode) : Variable(name, describer, creationType), fullName(), parseNode(parseNode), context(nullptr)
    { }

    const IParseNode* Characteristic::ParseNode() const { return parseNode; }

    void Characteristic::WithContext(const Context::ContextNode* const context)
    {
        if (this->context == nullptr)
            this->context = context;
    }

    const Context::ContextNode* Characteristic::Context() const { return context; }
}
