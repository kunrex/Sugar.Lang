#include "characteristic.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Characteristic::Characteristic(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const parseNode) : Variable(name, describer, creationType), parseNode(parseNode), context(nullptr)
    { }

    const IParseNode* Characteristic::ParseNode() const { return parseNode; }

    const IContextNode* Characteristic::Context() const { return context; }

    Characteristic::~Characteristic()
    {
        delete context;
    }
}
