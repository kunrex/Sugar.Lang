#ifndef CHILD_H
#define CHILD_H

namespace Services
{
    template <typename TParent>
    class Child
    {
        protected:
            TParent* parent;

            Child();

        public:
            [[nodiscard]] TParent* Parent() const;
            void SetParent(TParent* parent);

            virtual ~Child();
    };

    template <typename TParent>
    class ConstantChild : public Child<const TParent>
    {
        protected:
            ConstantChild();
    };
}

#endif
