#ifndef CIL_TRANSPILER_H
#define CIL_TRANSPILER_H

#include "../../../Services/string_builder.h"

#include "../../Structure/source_file.h"
#include "../../Structure/source_directory.h"
#include "../../Structure/Context/context_node.h"
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

            void PushTranscription();

            void TranspileDirectory(const Structure::SourceDirectory* directory);

            void TranspileFile(const Structure::SourceFile* file);
            void TranspileDataType(const Structure::Core::Interfaces::IUserDefinedType* dataType);

            void TranspileConstant(const Structure::Core::Interfaces::ICharacteristic* constant);
            void TranspileCharacteristic(const Structure::Core::Interfaces::ICharacteristic* characteristic);
            void TranspileEnumField(const Structure::Core::Interfaces::ICharacteristic* constant, const std::string& enumType);

            void TranspileFunction(const Structure::Core::Interfaces::IScoped* function);
            void TranspileConstructor(const Structure::Core::Interfaces::IScoped* constructor, const std::string& precursor);

            void TranspileFunctionBody(const Structure::Core::Interfaces::IScoped* scoped, const std::string& precursor);

            void TranspileScope(const Structure::Local::Scope* scope, Services::StringBuilder& stringBuilder, int& maxSlotSize);

        public:
            CILTranspiler(std::string name, std::string directory, const Structure::SourceDirectory* source);

            void Transpile();
            [[nodiscard]] const std::string& OutputFile() const;
    };
}

#endif
