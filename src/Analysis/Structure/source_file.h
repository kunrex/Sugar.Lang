#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include <vector>

#include "source_object.h"
#include "../../Lexing/Tokens/token.h"
#include "../../Parsing/ParseNodes/parse_node.h"
#include "../../Parsing/ParseNodes/Groups/source_file_node.h"
#include "../../Services/collection.h"

namespace Analysis::Structure
{
    class SourceFile final : public SourceObject, public Services::Collection<Core::DataType>
    {
        private:
            const std::string source;
            std::vector<Tokens::Token> tokens;

            std::vector<const Core::DataType*> references;

            ParseNodes::Groups::SourceFileNode* sourceNode;

        public:
            SourceFile(const std::string& name, std::string source);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            void AddChild(Core::DataType* child) override;

            void ReferenceThis(SourceObject* other) override;
            void AddReference(const Core::DataType* dataType) override;

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


#endif //SOURCE_FILE_H
