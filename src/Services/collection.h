#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>

namespace Services
{
    template <typename TChild>
    class Collection
    {
        protected:
            std::vector<TChild*> children;

            Collection();

        public:
            [[nodiscard]] int ChildCount() const;
            [[nodiscard]] const TChild* GetChild(int index) const;

            virtual void AddChild(TChild* child);

            typename std::vector<const TChild*>::const_iterator begin() const;
            typename std::vector<const TChild*>::const_iterator end() const;

            virtual ~Collection();
    };

    template <typename TChild>
    class ConstantCollection
    {
        protected:
            std::vector<const TChild*> children;

            ConstantCollection();

        public:
            [[nodiscard]] int ChildCount() const;
            [[nodiscard]] const TChild* GetChild(int index) const;

            virtual void AddChild(const TChild* child);

            typename std::vector<const TChild*>::const_iterator begin() const;
            typename std::vector<const TChild*>::const_iterator end() const;

            virtual ~ConstantCollection();
    };
}

#endif
