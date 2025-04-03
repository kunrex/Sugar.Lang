#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>

namespace Services
{
    template <typename TChild>
    class ICollection
    {
        public:
            [[nodiscard]] virtual int ChildCount() const = 0;

            [[nodiscard]] virtual TChild* GetChild(int index) const = 0;
            virtual void AddChild(TChild* child) = 0;

            virtual ~ICollection() = default;
    };

    template <typename TChild>
    class Collection : public virtual ICollection<TChild>
    {
        protected:
            std::vector<TChild*> children;

            Collection();

        public:
            [[nodiscard]] int ChildCount() const override;

            [[nodiscard]] TChild* GetChild(int index) const override;
            void AddChild(TChild* child) override;

            typename std::vector<TChild*>::const_iterator begin() const override;
            typename std::vector<TChild*>::const_iterator end() const override;

            ~Collection() override;
    };

    template <typename TChild>
    class ConstantCollection : public Collection<const TChild>
    {
        protected:
            ConstantCollection();
    };
}

#endif
