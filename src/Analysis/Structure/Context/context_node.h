#ifndef CONTEXT_NODE_H
#define CONTEXT_NODE_H

#include <array>
#include <tuple>
#include <vector>

#include "../Core/created.h"
#include "../Core/Interfaces/Context/i_context_node.h"

#include "../../../Parsing/ParseNodes/Enums/child_code.h"

namespace Analysis::Structure::Context
{
    class ContextNode : public Core::Created, public virtual Core::Interfaces::IContextNode
    {
        protected:
            explicit ContextNode(const Core::Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] uintptr_t Metadata() const override;

            [[nodiscard]] unsigned long ChildCount() const override;
            [[nodiscard]] const IContextNode* GetChild(int index) const override;
    };

    template <int childCount>
    class FixedContextCollection : public Core::Created, public virtual Core::Interfaces::IContextNode
    {
        protected:
            std::array<std::tuple<int, const IContextNode*>, childCount> children;

            void AddChild(ParseNodes::Enums::ChildCode code, const IContextNode* context);

            explicit FixedContextCollection(const Core::Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] uintptr_t Metadata() const override;

            [[nodiscard]] unsigned long ChildCount() const override;
            [[nodiscard]] const IContextNode* GetChild(int index) const override;

            void Print(const std::string& indent, bool last) const override;

            ~FixedContextCollection() override;
    };

    class DynamicContextCollection : public Core::Created, public virtual Core::Interfaces::IContextNode
    {
        protected:
            std::vector<const IContextNode*> children;

            explicit DynamicContextCollection(const Core::Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] uintptr_t Metadata() const override;

            [[nodiscard]] unsigned long ChildCount() const override;
            [[nodiscard]] const IContextNode* GetChild(int index) const override;

            void AddChild(const IContextNode* child);

            void Print(const std::string& indent, bool last) const override;

            ~DynamicContextCollection() override;
    };
}

#endif
