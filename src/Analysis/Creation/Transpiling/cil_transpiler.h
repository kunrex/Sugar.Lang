#ifndef CIL_TRANSPILER_H
#define CIL_TRANSPILER_H

#include "../../../Services/string_builder.h"

#include "../../Structure/source_file.h"
#include "../../Structure/source_directory.h"
#include "../../Structure/Context/context_node.h"
#include "../../Structure/Global/Variables/enum_field.h"
#include "../../Structure/Core/Interfaces/Scoped/i_scoped.h"
#include "../../Structure/Global/Variables/global_constant.h"

namespace Analysis::Creation
{
    class CILTranspiler final
    {
        private:
            const std::string projectName;
            const std::string projectDirectory;

            std::string projectLocation;

            const Structure::SourceDirectory* source;

            Services::StringBuilder stringBuilder;

            void CILTranspiler::TranspileDirectory(const Structure::SourceDirectory* directory);

            void CILTranspiler::TranspileFile(const Structure::SourceFile* file);
            void CILTranspiler::TranspileDataType(const Structure::Core::Interfaces::IUserDefinedType* dataType);

            void CILTranspiler::TranspileConstant(const Structure::Global::GlobalConstant* constant);
            void CILTranspiler::TranspileCharacteristic(const Structure::Core::Interfaces::ICharacteristic* characteristic);

            void CILTranspiler::TranspileFunction(const Structure::Core::Interfaces::IScoped* function);
            void CILTranspiler::TranspileConstructor(const Structure::Core::Interfaces::IScoped* constructor);

            void CILTranspiler::TranspileFunctionBody(const Structure::Core::Interfaces::IScoped* scoped);

            void CILTranspiler::TranspileScope(const Structure::Local::Scope* scope, Services::StringBuilder& stringBuilder, int& maxSlotSize);

            void CILTranspiler::TranspileContext(const Structure::Context::ContextNode* context, Services::StringBuilder& stringBuilder);

        public:
            CILTranspiler(std::string name, std::string directory, const Structure::SourceDirectory* source);

            void Transpile();
            [[nodiscard]] const std::string& OutputFile() const;
    };
}

#endif
