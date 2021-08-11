
#ifndef enumerate_H

#define enumerate_H

#include <iterator>
#include <tuple>

namespace zips
{

template <typename ObjIt>
class enumerateIterator
{
public:
    using iterator_category = typename std::iterator_traits<ObjIt>::iterator_category;
    using difference_type   = typename std::iterator_traits<ObjIt>::difference_type;
    using value_type        = std::tuple<int, typename std::iterator_traits<ObjIt>::value_type>;
    using pointer           = typename std::iterator_traits<ObjIt>::pointer;
    using reference         = std::tuple<int, typename std::iterator_traits<ObjIt>::value_type&>;

public:
    enumerateIterator(ObjIt&& p_it, int p_i=0) : m_it(p_it), i(p_i) {}

    reference operator*() { return std::forward_as_tuple(i, *m_it); }
    pointer  operator->() { return m_it.operator->(); }

    enumerateIterator& operator++()
    {
        ++m_it;
        ++i;
        return *this;
    }
    enumerateIterator operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const enumerateIterator& other) { return m_it == other.m_it; }
    bool operator!=(const enumerateIterator& other) { return m_it != other.m_it; }

private:
    ObjIt m_it;
    int i;
};

template <typename Obj>
class enumerate
{
public:
    using iterator = enumerateIterator<typename Obj::iterator>;
public:
    enumerate(Obj& p_obj, int start=0) : m_obj(p_obj), i(start) {}

    iterator begin() { return iterator(m_obj.begin(), i); }
    iterator end()   { return iterator(m_obj.end()); }
private:
    Obj& m_obj;
    int i;
};

}


#endif // enumerate_H