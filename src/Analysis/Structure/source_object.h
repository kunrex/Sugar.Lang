#ifndef SOURCE_OBJECT_H
#define SOURCE_OBJECT_H

#include "../../Services/child.h"
#include "../../Services/printable.h"

#include "Enums/source_type.h"

#include "Core/nameable.h"
#include "Core/Interfaces/i_bindable.h"
#include "Core/Interfaces/i_transpilable.h"

namespace Analysis::Structure
{
    class SourceObject : public Core::Nameable, public Services::Child<SourceObject>, public Services::Printable, public virtual Core::Interfaces::IGloballyBindable, public virtual Core::Interfaces::ILocallyBindable, public virtual Core::Interfaces::ITranspilable
    {
        protected:
            mutable std::string fullName;

        public:
            explicit SourceObject(const std::string& name);

            [[nodiscard]] virtual Enums::SourceType SourceType() const = 0;

            [[nodiscard]] const std::string& FullName() const override;

            virtual void LexParse() = 0;
            virtual void InitDataTypes() = 0;
            virtual void ManageImports() = 0;
    };
}

#endif
