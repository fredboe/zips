
#ifndef zip2_H

#define zip2_H

#include <iostream>
#include <iterator>
#include <tuple>

template <typename It1, typename It2>
class zip_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::tuple<typename It1::value_type, typename It2::value_type>;
    using reference = std::tuple<typename It1::value_type&, typename It2::value_type&>;
public:
    zip_iterator(It1&& it1, It2&& it2) : m_it1(std::move(it1)), m_it2(std::move(it2)) {}

    reference operator*()
    {
        return std::forward_as_tuple(*m_it1, *m_it2);
    }
    
    zip_iterator& operator++()
    {
        ++m_it1;
        ++m_it2;
        return *this;
    }
    zip_iterator operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const zip_iterator& other)
    {
        return m_it1 == other.m_it1 || m_it2 == other.m_it2;
    }
    bool operator!=(const zip_iterator& other)
    {
        return m_it1 != other.m_it1 && m_it2 != other.m_it2;
    }

private:
    It1 m_it1;
    It2 m_it2;
};

template <typename T1, typename T2>
class zip2
{
public:
    using iterator = zip_iterator<typename T1::iterator, typename T2::iterator>;
public:
    zip2(const T1& obj1, const T2& obj2) : m_obj1(obj1), m_obj2(obj2) {}
    zip2(const T1& obj1, T2&& obj2) : m_obj1(obj1), m_obj2(std::move(obj2)) {}
    zip2(T1&& obj1, const T2& obj2) : m_obj1(std::move(obj1)), m_obj2(obj2) {}
    zip2(T1&& obj1, T2&& obj2) : m_obj1(std::move(obj1)), m_obj2(std::move(obj2)) {}
    
    iterator begin()
    {
        return iterator(m_obj1.begin(), m_obj2.begin());
    }

    iterator end()
    {
        return iterator(m_obj1.end(), m_obj2.end());
    }

private:
    T1 m_obj1;
    T2 m_obj2;
};

#endif // zip2_H
