#ifndef zip_H

#define zip_H

#include <tuple>
#include <iterator>
#include <utility>

namespace zips
{

template <typename ... Its>
class zip_iterator
{
public:
    using iterator_category = std::common_type_t<typename std::iterator_traits<Its>::iterator_category...>;
    using difference_type   = std::common_type_t<typename std::iterator_traits<Its>::difference_type...>;
    using value_type        = std::tuple<typename std::iterator_traits<Its>::value_type ...>;
    using pointer           = std::tuple<typename std::iterator_traits<Its>::pointer ...>;
    using reference         = std::tuple<std::remove_reference_t<typename std::iterator_traits<Its>::reference>& ...>;

public:
    zip_iterator(std::tuple<Its ...>&& p_iterators) : iterators(std::move(p_iterators)) {}

    reference operator*()
    {
        return std::apply([] (auto& ... it) { return std::forward_as_tuple((*it) ...); },
                            iterators);
    }

    zip_iterator& operator++()
    {
        inc_tup();
        return *this;
    }
    zip_iterator operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const zip_iterator<Its ...>& other)
    {
        return eq_tup(other);
    }
    bool operator!=(const zip_iterator<Its ...>& other)
    {
        return !(*this == other);
    }
private:
    void inc_tup()
    {
        constexpr std::size_t N = std::tuple_size<decltype(iterators)>::value;
        inc_tup_impl(std::make_index_sequence<N>{});
    }
    template <std::size_t ... Is>
    void inc_tup_impl(std::index_sequence<Is ...>)
    {
        auto increment = [] (auto& it) { ++it; };
        (..., increment(std::get<Is>(iterators)));
    }

    bool eq_tup(const zip_iterator<Its ...>& other)
    {
        constexpr std::size_t N = std::tuple_size<decltype(iterators)>::value;
        return eq_tup_impl(other, std::make_index_sequence<N>{});
    }
    template <std::size_t ... Is>
    bool eq_tup_impl(const zip_iterator<Its ...>& other, std::index_sequence<Is ...>)
    {
        return (... || (std::get<Is>(iterators) == std::get<Is>(other.iterators)));
    }

private:
    std::tuple<Its ...> iterators;
};

template <typename ... Objs>
class zip
{
public:
    using iterator = zip_iterator<typename Objs::iterator ...>;

public:
    zip(Objs& ... p_objs) : objs(std::forward_as_tuple(p_objs...)) {}

    iterator begin()
    {
        return iterator(std::apply([] (auto& ... x) { return std::make_tuple(x.begin() ...); }, objs));
    }

    iterator end()
    {
        return iterator(std::apply([] (auto& ... x) { return std::make_tuple(x.end() ...); }, objs));
    }

private:
    std::tuple<Objs& ...> objs;
};

} // end namespace zips



#endif // zip_H

// C++17