#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include "variable.h"

#include "../Interfaces/Creation/i_characteristic.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Core
{
    class Characteristic : public Global::GlobalNode, public Variable, public virtual Interfaces::ICharacteristic
    {
        protected:
            mutable std::string fullName;

            const ParseNodes::Core::Interfaces::IParseNode* parseNode;

            const Context::ContextNode* context;

            Characteristic(const std::string& name, Enums::Describer describer, const Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* parseNode);

        public:
            [[nodiscard]] const ParseNodes::Core::Interfaces::IParseNode* ParseNode() const override;

            void WithContext(const Context::ContextNode* context) override;
            [[nodiscard]] const Context::ContextNode* Context() const override;
    };
}

#endif
