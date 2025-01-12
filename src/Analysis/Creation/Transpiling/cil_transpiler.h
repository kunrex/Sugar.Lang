#ifndef CIL_TRANSPILER_H
#define CIL_TRANSPILER_H

#include "../../Structure/source_file.h"
#include "../../Structure/source_directory.h"
#include "../../../Services/singleton_service.h"
#include "../../Structure/Nodes/Context/context_node.h"

namespace Analysis::Creation
{
    class CILTranspiler final : public Services::SingletonService<CILTranspiler>
    {
        private:
            const std::string projectName;
            const std::string projectDirectory;

            std::string source;

            void TranspileFile(const Structure::SourceFile* file);
            void TranspileDirectory(const Structure::SourceDirectory* directory);

            void TranspileDataType(const Structure::Core::DataType* dataType);

            void TranspileEntity(const std::string& indent, const Structure::Context::ContextNode* entity);
            void TranspileEntityInit(const std::string& indent, const Structure::Context::ContextNode* entity);
        public:
            CILTranspiler(std::string name, std::string directory);

            [[nodiscard]] bool TryCreateFile() const;

            void Transpile(const Structure::SourceDirectory* directory);
    };
}

#endif
