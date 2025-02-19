#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include "variable.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Core
{
    class Characteristic : public Global::GlobalNode, public Variable
    {
        protected:
            const ParseNodes::ParseNode* parseNode;

            Characteristic(const std::string& name, Enums::Describer describer, const DataType* creationType, const ParseNodes::ParseNode* parseNode);

        public:
            [[nodiscard]] const ParseNodes::ParseNode* ParseNode() const;
    };
}

#endif
