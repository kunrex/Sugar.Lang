#include "dictionary.h"

namespace Services
{
    template <typename TKey, typename TValue>
    Dictionary<TKey, TValue>::Dictionary() : map()
    { }

    template <typename TKey, typename TValue>
    int Dictionary<TKey, TValue>::ChildCount() const { return map.size(); }

    template <typename TKey, typename TValue>
    TValue* Dictionary<TKey, TValue>::Get(TKey key) const
    {
        auto it = map.find(key);
        return it == map.end() ? nullptr : it->second;
    }

    template <typename TKey, typename TValue>
    bool Dictionary<TKey, TValue>::Push(TKey key, TValue* value)
    {
        auto it = map.find(key);
        if (it == map.end())
            map[key] = value;

        return it == map.end();
    }

    template <typename TKey, typename TValue>
    typename std::unordered_map<TKey, TValue*>::const_iterator Dictionary<TKey, TValue>::begin() const
    {
        return map.begin();
    }

    template <typename TKey, typename TValue>
    typename std::unordered_map<TKey, TValue*>::const_iterator Dictionary<TKey, TValue>::end() const
    {
        return map.end();
    }

    template <typename TKey, typename TValue>
    std::vector<TKey> Dictionary<TKey, TValue>::keys() const
    {
        std::vector<TKey> keys;
        keys.reserve(map.size());

        for (const auto& pair : map) {
            keys.push_back(pair.first);
        }

        return keys;
    }

    template <typename TKey, typename TValue>
    std::vector<TValue*> Dictionary<TKey, TValue>::values() const
    {
        std::vector<TValue*> values;
        values.reserve(map.size());

        for (const auto& pair : map) {
            values.push_back(pair.second);
        }

        return values;
    }

    template <typename TKey, typename TValue>
    Dictionary<TKey, TValue>::~Dictionary()
    {
        for (auto it = map.begin(); it != map.end(); ++it)
            delete it->second;
    }
}
