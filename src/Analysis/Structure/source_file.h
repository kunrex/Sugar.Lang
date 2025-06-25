#ifndef SOURCE_FILE_H
#define SOURCE_FILE_H

#include <vector>

#include "source_object.h"

#include "Core/Interfaces/DataTypes/i_data_type.h"

#include "../../Services/dictionary.h"

#include "../../Lexing/Tokens/token.h"

#include "../../Parsing/ParseNodes/Groups/source_file_node.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IUserDefinedType;
}

namespace Analysis::Structure
{
    class SourceFile final : public SourceObject, public Services::Dictionary<std::string, Core::Interfaces::IUserDefinedType>
    {
        private:
            const std::string source;
            std::vector<Tokens::Token> tokens;

            ParseNodes::Groups::SourceFileNode* sourceNode;

            std::unordered_map<std::string, const Core::Interfaces::IDataType*> references;

        public:
            SourceFile(const std::string& name, std::string source);

            [[nodiscard]] Enums::SourceType SourceType() const override;

            bool AddChild(std::string key, Core::Interfaces::IUserDefinedType* value) override;

            void AddReference(const Core::Interfaces::IDataType* dataType);
            [[nodiscard]] const Core::Interfaces::IDataType* GetReference(const std::string& name) const;

            [[nodiscard]] unsigned long SourceLength() const;
            [[nodiscard]] char SourceAt(unsigned long i) const;

            void PushBackToken(Tokens::Token token);
            [[nodiscard]] unsigned long TokenCount() const;
            [[nodiscard]] const Tokens::Token& TokenAt(unsigned long i) const;

            [[nodiscard]] const ParseNodes::Groups::SourceFileNode* SourceNode() const;

            void LexParse() override;
            void InitDataTypes() override;
            void ManageImports() override;

            void BindGlobal() override;
            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void Print(const std::string& indent, bool last) const override;

            ~SourceFile() override;
    };
}

#endif
