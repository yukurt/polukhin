#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/type_traits/has_pre_increment.hpp>

#include <cstdio>

namespace detail {
struct pre_inc_functor {
    template <class T>
    void operator()(T& value) const {
        printf("%s\n", __FUNCTION__);
        ++value;
    }
};

struct post_inc_functor {
    template <class T>
    void operator()(T& value) const {
        printf("%s\n", __FUNCTION__);
        value++;
    }
};

struct plus_assignable_functor {
    template <class T>
    void operator()(T& value) const {
        printf("%s\n", __FUNCTION__);
        value += T(1);
    }
};

struct plus_functor {
    template <class T>
    void operator()(T& value) const {
        printf("%s\n", __FUNCTION__);
        value = value + T(1);
    }
};
}

template <class T>
void inc(T& value) {
    typedef detail::plus_functor step_0_t;

    typedef typename boost::conditional<
        boost::has_plus_assign<T>::value,
        detail::plus_assignable_functor,
        step_0_t
    >::type step_1_t;

    typedef typename boost::conditional<
        boost::has_post_increment<T>::value,
        detail::post_inc_functor,
        step_1_t
    >::type step_2_t;

    typedef typename boost::conditional<
        boost::has_pre_increment<T>::value,
        detail::pre_inc_functor,
        step_2_t
    >::type step_3_t;

    step_3_t() // default constructing functor
    (value); // calling operator() of a functor
}

class cls
{
public:
    cls(int val): m_int(val) {}

    cls operator+=(cls const& rhs)
    {
        printf("%s\n", __FUNCTION__);
        return cls(++m_int);
    }

    int get()
    {
        return m_int;
    }

private:
    int m_int;
};

int main()
{
    int x = 5;
    inc(x);
    printf("x = %d\n", x);

    cls y(89);
    inc(y);
    printf("y = %d\n", y.get());

    return 0;
}
