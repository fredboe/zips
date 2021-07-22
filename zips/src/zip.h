#ifndef zip_H

#define zip_H

#include <tuple>
#include <iterator>
#include <utility>

template <typename ... Its>
class zip_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::tuple<typename Its::value_type ...>;
    using reference = std::tuple<typename Its::value_type& ...>;

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
        //using N = std::tuple_size<decltype(iterators)>::value;
        inc_tup_impl(std::make_index_sequence<std::tuple_size<decltype(iterators)>::value>{});
    }
    template <std::size_t ... Is>
    void inc_tup_impl(std::index_sequence<Is ...>)
    {
        auto increment = [] (auto& it) { ++it; };
        (..., increment(std::get<Is>(iterators)));
    }

    bool eq_tup(const zip_iterator<Its ...>& other)
    {
        //using N = std::tuple_size<decltype(iterators)>::value;
        return eq_tup_impl(other, std::make_index_sequence<std::tuple_size<decltype(iterators)>::value>{});
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
    zip(Objs& ... p_objs) : objs(std::make_tuple(p_objs...)) {}

    iterator begin()
    {
        return iterator(std::apply([](auto& ... x) { return std::make_tuple(x.begin() ...); }, objs));
    }

    iterator end()
    {
        return iterator(std::apply([](auto& ... x) { return std::make_tuple(x.end() ...); }, objs));
    }

private:
    std::tuple<Objs...> objs;
};



#endif // zip_H

// C++17