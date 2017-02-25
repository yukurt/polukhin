#include <iostream>

#include <boost/mpl/size.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/add_const.hpp>

#include <boost/mpl/transform.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>

// Make unsigned
struct unsigne; // No typo: 'unsigned' is a keyword, we cannot use it.

// Make constant
struct constant;

// Otherwise we do not change type
struct no_change;

template <class Types, class Modifiers>
struct do_modifications
{
    BOOST_STATIC_ASSERT((boost::is_same<
        typename boost::mpl::size<Types>::type,
        typename boost::mpl::size<Modifiers>::type
    >::value));

    typedef boost::mpl::if_<
        boost::is_same<boost::mpl::_2, unsigne>,
        boost::make_unsigned<boost::mpl::_1>,
        boost::mpl::if_<
            boost::is_same<boost::mpl::_2, constant>,
            boost::add_const<boost::mpl::_1>,
            boost::mpl::_1
        >
    > binary_operator_t;

    typedef typename boost::mpl::transform<
        Types,
        Modifiers,
        binary_operator_t
    >::type type;
};

typedef boost::mpl::vector<unsigne, no_change, constant, unsigne> modifiers;
typedef boost::mpl::vector<int, char, short, long> types;
typedef do_modifications<types, modifiers>::type result_type;

BOOST_STATIC_ASSERT((boost::is_same<
    boost::mpl::at_c<result_type, 0>::type,
    unsigned int
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
    boost::mpl::at_c<result_type, 1>::type,
    char
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
    boost::mpl::at_c<result_type, 2>::type,
    const short
>::value));

BOOST_STATIC_ASSERT((boost::is_same<
    boost::mpl::at_c<result_type, 3>::type,
    unsigned long
>::value));

int main(int argc, char *argv[])
{
    auto x = 78;
    std::cout << "Hello World! " << x << std::endl;
    return 0;
}
