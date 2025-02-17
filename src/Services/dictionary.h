#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <unordered_map>

namespace Services
{
    template <typename TKey, typename TValue>
    class Dictionary
    {
        protected:
            std::unordered_map<TKey, TValue*> map;

            Dictionary();

        public:
            [[nodiscard]] int ChildCount() const;
            [[nodiscard]] TValue* Get(TKey key) const;

            virtual bool Push(TKey key, TValue* value);

            typename std::unordered_map<TKey, TValue*>::const_iterator begin() const;
            typename std::unordered_map<TKey, TValue*>::const_iterator end() const;

            std::vector<TKey> keys() const;
            std::vector<TValue*> values() const;

            virtual ~Dictionary();
    };
}

#endif
