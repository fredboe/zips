#ifndef enumerate_H

#define enumerate_H

#include <iterator>
#include <tuple>

namespace zips
{

// It is an iterator
template <typename It>
class enumerate_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::tuple<int, typename It::value_type&>;
    using difference_type   = typename It::difference_type;
    using reference         = value_type;
    using pointer           = typename It::pointer;
public:
    enumerate_iterator(It&& object, int start) : m_object(std::move(object)), m_num(start) {}

    reference operator*()
    {
        return std::forward_as_tuple(m_num, *m_object);
    }

    enumerate_iterator& operator++()
    {
        ++m_num;
        ++m_object;
        return *this;
    }
    enumerate_iterator operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const enumerate_iterator& other)
    {
        return m_object == other.m_object;
    }
    bool operator!=(const enumerate_iterator& other)
    {
        return m_object != other.m_object;
    }

private:
    It m_object;
    int m_num;
};

// It is an iterator
template <typename It>
class const_enumerate_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::tuple<int, const typename It::value_type&>;
    using difference_type   = typename It::difference_type;
    using reference         = value_type;
    using pointer           = typename It::pointer;
public:
    const_enumerate_iterator(It&& object, int start) : m_object(std::move(object)), m_num(start) {}

    reference operator*()
    {
        return std::forward_as_tuple(m_num, *m_object);
    }

    const_enumerate_iterator& operator++()
    {
        ++m_num;
        ++m_object;
        return *this;
    }
    const_enumerate_iterator operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const const_enumerate_iterator& other)
    {
        return m_object == other.m_object;
    }
    bool operator!=(const const_enumerate_iterator& other)
    {
        return m_object != other.m_object;
    }

private:
    It m_object;
    int m_num;
};

template <typename T>
class enumerate
{
public:
    using iterator       = enumerate_iterator<typename T::iterator>;
    using const_iterator = const_enumerate_iterator<typename T::const_iterator>;
public:
    enumerate(T& container) : m_container(container), m_start(0) {}
    enumerate(T& container, int start) : m_container(container), m_start(start) {}

    iterator begin()
    {
        return iterator(m_container.begin(), m_start);
    }
    iterator end()
    {
        return iterator(m_container.end(), m_start);
    }

    const_iterator cbegin()
    {
        return const_iterator(m_container.cbegin(), m_start);
    }
    const_iterator cend()
    {
        return const_iterator(m_container.cend(), m_start);
    }

private:
    T& m_container;
    int m_start;
};

}

#endif // enumerate_H