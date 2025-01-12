#ifndef CHILD_H
#define CHILD_H

namespace Services
{
    template <typename TParent>
    class Child
    {
        protected:
            const TParent* parent;

            Child();

        public:
            [[nodiscard]] const TParent* Parent() const;

            virtual void SetParent(const TParent* parent);

            virtual ~Child();
    };
}

#endif
