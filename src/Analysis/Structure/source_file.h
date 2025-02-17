#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include <vector>

#include "../../Services/dictionary.h"

#include "../../Lexing/Tokens/token.h"

#include "../../Parsing/ParseNodes/Groups/source_file_node.h"

#include "source_object.h"

namespace Analysis::Structure
{
    class SourceFile final : public SourceObject, public Services::Dictionary<std::string, Core::DataType>
    {
        private:
            const std::string source;
            std::vector<Tokens::Token> tokens;

            ParseNodes::Groups::SourceFileNode* sourceNode;

            Dictionary<std::string, const Core::DataType> references;

        public:
            SourceFile(const std::string& name, std::string source);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            bool Push(std::string key, Core::DataType* value) override;

            void ReferenceThis(SourceObject* other) override;
            void AddReference(const Core::DataType* dataType) override;
            [[nodiscard]] const Core::DataType* GetReference(const std::string& name) const;

            [[nodiscard]] unsigned long SourceLength() const;
            [[nodiscard]] char SourceAt(unsigned long i) const;

            void PushBackToken(Tokens::Token token);
            [[nodiscard]] unsigned long TokenCount() const;
            [[nodiscard]] const Tokens::Token& TokenAt(unsigned long i);

            void WithSourceNode(ParseNodes::Groups::SourceFileNode* source);
            [[nodiscard]] const ParseNodes::Groups::SourceFileNode* SourceNode() const;

            ~SourceFile() override;
    };
}

#endif
