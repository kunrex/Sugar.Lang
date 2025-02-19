#ifndef CIL_TRANSPILER_H
#define CIL_TRANSPILER_H

#include "../../../Services/string_builder.h"
#include "../../../Services/singleton_service.h"

#include "../../Structure/source_directory.h"
#include "../../Structure/source_file.h"

namespace Analysis::Creation
{
    class CILTranspiler final
    {
        private:
            const std::string projectName;
            const std::string projectDirectory;

            const Structure::SourceDirectory* source;

            bool isExecutable;
            Services::StringBuilder* stringBuilder;

            void CILTranspiler::TranspileDirectory(const Structure::SourceDirectory* directory);

            void CILTranspiler::TranspileFile(const Structure::SourceFile* file);
            void CILTranspiler::TranspileDataType(const Structure::Core::DataType* dataType);

        public:
            CILTranspiler(std::string name, std::string directory, const Structure::SourceDirectory* source);

            void Transpile() const;
            [[nodiscard]] const std::string& OutputFile() const;

            ~CILTranspiler();
    };
}

#endif
