#pragma once

#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace tg
{
    template<typename KeyType, typename ValueType, typename IndexType>
    class SparseMap;

    template<typename KeyType,
             typename ValueType,
             typename IndexType,
             typename ReferenceType,
             typename KeyStorageType,
             typename ValueStorageType>
    class SparseMapIterator
    {
        friend class SparseMap<KeyType, ValueType, IndexType>;

    public:
        SparseMapIterator(const SparseMapIterator& p_other)
            : SparseMapIterator(p_other.m_index, p_other.m_keys, p_other.m_values)
        {}

        bool operator!=(const SparseMapIterator& p_other) const
        {
            return m_index != p_other.m_index || &m_keys != &(p_other.m_keys) || &m_values != &(p_other.m_values);
        }

        bool operator==(const SparseMapIterator& p_other) const
        {
            return m_index == p_other.m_index && &m_keys == &(p_other.m_keys) && &m_values == &(p_other.m_values);
        }

        [[nodiscard]] std::pair<KeyType, ReferenceType> operator*() const
        {
            return { m_keys[m_index], m_values[m_index] };
        }

        SparseMapIterator& operator++()
        {
            ++m_index;
            return *this;
        }

        SparseMapIterator operator++(int)
        {
            auto tmp = SparseMapIterator(*this);
            ++m_index;
            return tmp;
        }

        SparseMapIterator& operator--()
        {
            --m_index;
            return *this;
        }

        SparseMapIterator operator--(int)
        {
            auto tmp = SparseMapIterator(*this);
            --m_index;
            return tmp;
        }

        KeyType       key() { return m_keys[m_index]; }
        ReferenceType value() { return m_values[m_index]; }

    private:
        SparseMapIterator(std::size_t p_index, KeyStorageType p_keys, ValueStorageType p_values)
            : m_index(p_index)
            , m_keys(p_keys)
            , m_values(p_values)
        {}

    private:
        std::size_t      m_index;
        KeyStorageType   m_keys;
        ValueStorageType m_values;
    };

    template<typename KeyType>
    struct SparseIndex
    {
        static_assert(std::is_constructible_v<std::size_t, KeyType>,
                      "The type 'KeyType' can not be converted into std::size_t");

        std::size_t operator()(const KeyType& p_key) const noexcept { return static_cast<std::size_t>(p_key); }
    };

    template<typename KeyType, typename ValueType, typename IndexType = SparseIndex<KeyType>>
    class SparseMap
    {
        using ValueStorage = std::vector<ValueType>;
        using KeyStorage = std::vector<KeyType>;

        struct SparseEntry
        {
            bool        valid;
            std::size_t index;

            SparseEntry()
                : valid(false)
                , index(0)
            {}

            SparseEntry(std::size_t p_index)
                : valid(true)
                , index(index)
            {}
        };

        using SparseStorage = std::vector<SparseEntry>;

    public:
        using key_type = KeyType;
        using value_type = ValueType;
        using reference = ValueType&;
        using const_reference = const ValueType&;
        using iterator = SparseMapIterator<KeyType, ValueType, IndexType, ValueType&, KeyStorage&, ValueStorage&>;
        using const_iterator =
            SparseMapIterator<KeyType, ValueType, IndexType, const ValueType&, const KeyStorage&, const ValueStorage&>;

    public:
        std::pair<bool, iterator> insert(KeyType p_key, const ValueType& p_value)
        {
            auto res = emplaceImpl(std::move(p_key), p_value);
            return { true, { res.second, m_keys, m_values } };
        }

        std::pair<bool, iterator> insert(KeyType p_key, ValueType&& p_value)
        {
            auto res = emplaceImpl(std::move(p_key), std::move(p_value));
            return { true, { res.second, m_keys, m_values } };
        }

        template<typename... Args>
        std::pair<bool, reference> emplace(KeyType p_key, Args&&... p_args)
        {
            auto res = emplaceImpl(std::move(p_key), std::forward<Args>(p_args)...);
            return { res.first, m_values[res.second] };
        }

        void erase(KeyType p_key)
        {
            const auto sparseIndex = m_index(p_key);
            if (sparseIndex >= m_sparse.size())
            {
                return;
            }

            auto& sparseEntry = m_sparse[sparseIndex];

            if (!sparseEntry.valid)
            {
                return;
            }

            auto& value = m_values[sparseEntry.index];
            auto& key = m_keys[sparseEntry.index];

            auto& lastvalue = m_values.back();
            auto& lastKey = m_keys.back();

            std::swap(value, lastvalue);
            std::swap(key, lastKey);

            auto& movedSparseEntry = m_sparse[m_index(key)];

            movedSparseEntry.index = sparseEntry.index;

            m_values.pop_back();
            m_keys.pop_back();

            sparseEntry.valid = false;
            sparseEntry.index = 0;

            if (!movedSparseEntry.valid)
            {
                return;
            }

            dive(movedSparseEntry.index);
        }

        reference operator[](KeyType p_key)
        {
            auto res = emplaceImpl(std::move(p_key));
            return m_values[res.second];
        }

        const_reference at(KeyType p_key) const { return m_values[m_sparse[m_index(p_key)].index]; }

        reference at(KeyType p_key) { return m_values[m_sparse[m_index(p_key)].index]; }

        const_iterator cbegin() const { return { 0, m_keys, m_values }; }
        const_iterator cend() const { return { m_values.size(), m_keys, m_values }; }

        iterator begin() { return { 0, m_keys, m_values }; }
        iterator end() { return { m_values.size(), m_keys, m_values }; }

        const_iterator find(KeyType p_key) const
        {
            auto sparseIndex = m_index(p_key);
            if (sparseIndex >= m_sparse.size())
            {
                return cend();
            }

            auto& sparseEntry = m_sparse[sparseIndex];
            if (!sparseEntry.valid)
            {
                return cend();
            }

            return { sparseEntry.index, m_keys, m_values };
        }

        iterator find(KeyType p_key)
        {
            auto sparseIndex = m_index(p_key);
            if (sparseIndex >= m_sparse.size())
            {
                return end();
            }

            auto& sparseEntry = m_sparse[sparseIndex];
            if (!sparseEntry.valid)
            {
                return end();
            }

            return { sparseEntry.index, m_keys, m_values };
        }

        const KeyStorage&   keys() const { return m_keys; }
        const ValueStorage& values() const { return m_values; }

    private:
        std::size_t dive(std::size_t p_index)
        {
            const auto lastDenseIndex = m_values.size() - 1;

            if (p_index == lastDenseIndex)
            {
                return p_index;
            }

            std::size_t currentIndex = p_index;
            std::size_t rightIndex = p_index + 1;

            auto currentKey = m_index(m_keys[currentIndex]);
            auto rightKey = m_index(m_keys[rightIndex]);

            while (currentKey > rightKey)
            {
                std::swap(m_values[currentIndex], m_values[rightIndex]);
                std::swap(m_keys[currentIndex], m_keys[rightIndex]);
                std::swap(m_sparse[currentKey].index, m_sparse[rightKey].index);

                ++currentIndex;
                ++rightIndex;

                if (currentIndex == lastDenseIndex)
                {
                    break;
                }

                currentKey = m_index(m_keys[currentIndex]);
                rightKey = m_index(m_keys[rightIndex]);
            }

            return currentIndex;
        }

        std::size_t ascent(std::size_t p_index)
        {
            if (p_index == 0)
            {
                return p_index;
            }

            std::size_t currentIndex = p_index;
            std::size_t leftIndex = p_index - 1;

            auto currentKey = m_index(m_keys[currentIndex]);
            auto leftKey = m_index(m_keys[leftIndex]);

            while (currentKey < leftKey)
            {
                std::swap(m_values[currentIndex], m_values[leftIndex]);
                std::swap(m_keys[currentIndex], m_keys[leftIndex]);
                std::swap(m_sparse[currentKey].index, m_sparse[leftKey].index);

                --currentIndex;
                --leftIndex;

                if (currentIndex == 0)
                {
                    break;
                }

                currentKey = m_index(m_keys[currentIndex]);
                leftKey = m_index(m_keys[leftIndex]);
            }

            return currentIndex;
        }

        template<typename... Args>
        std::pair<bool, std::size_t> emplaceImpl(KeyType p_key, Args&&... p_args)
        {
            auto sparseIndex = m_index(p_key);

            if (sparseIndex >= m_sparse.capacity())
            {
                std::size_t newSize = 1;
                while (newSize <= sparseIndex)
                {
                    newSize = newSize << 1;
                }

                m_sparse.reserve(newSize);
            }

            if (sparseIndex >= m_sparse.size())
            {
                m_sparse.resize(sparseIndex + 1, SparseEntry{});
            }

            const auto denseSize = m_values.size();

            if (denseSize == m_values.capacity())
            {
                std::size_t newSize = 1;
                while (newSize <= denseSize)
                {
                    newSize = newSize << 1;
                }

                m_values.reserve(newSize);
                m_keys.reserve(newSize);
            }

            auto& sparseEntry = m_sparse[sparseIndex];
            if (sparseEntry.valid)
            {
                return { false, sparseEntry.index };
            }

            auto& denseEntry = m_values.emplace_back(std::forward<Args>(p_args)...);
            m_keys.push_back(std::move(p_key));

            sparseEntry.valid = true;
            sparseEntry.index = denseSize;

            auto newIndex = ascent(denseSize);

            return { true, newIndex };
        }

    private:
        IndexType     m_index;
        ValueStorage  m_values;
        KeyStorage    m_keys;
        SparseStorage m_sparse;
    };
}
