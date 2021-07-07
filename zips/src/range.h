#ifndef range_H

#define range_H


#include <iostream>
#include <iterator>

class range_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int*;
    using reference = int&;
public:
    range_iterator(int val, int step) : m_val(val), m_step(step) {}
    range_iterator(const range_iterator& other) : m_val(other.m_val), m_step(other.m_step) {}
    range_iterator(range_iterator&& other) noexcept
    {
        m_val  = other.m_val;
        m_step = other.m_step;

        other.m_val  = 0;
        other.m_step = 0;
    }

    reference operator*()
    {
        return m_val;
    }

    range_iterator& operator++()
    {
        m_val += m_step;
        return *this;
    }
    range_iterator operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const range_iterator& other)
    {
        return m_val == other.m_val;
    }
    bool operator!=(const range_iterator& other)
    {
        return m_val != other.m_val;
    }

private:
    int m_val;
    int m_step;
};

class range
{
public:
    using iterator = range_iterator;
    using const_iterator = range_iterator;
public:
    range(int end) : m_start(0), m_end(end), m_step(1) {}
    range(int start, int end) : m_start(start), m_end(end), m_step(1) {}
    range(int start, int end, int step) : m_start(start), m_end(end), m_step(step) {}

    range(const range& other) 
        : m_start(other.m_start), m_end(other.m_end), m_step(other.m_step) {}
    range(range&& other) noexcept
    {
        m_start = other.m_start;
        m_end   = other.m_end;
        m_step  = other.m_step;

        other.m_start = 0;
        other.m_end   = 0;
        other.m_step  = 0;
    }


    iterator begin()
    {
        return iterator(m_start, m_step);
    }

    iterator end()
    {
        return iterator(m_end, m_step);
    }


    const_iterator cbegin()
    {
        return const_iterator(m_start, m_step);
    }

    const_iterator cend()
    {
        return const_iterator(m_end, m_step);
    }


private:
    int m_start;
    int m_end;
    int m_step;
};


#endif // range_H