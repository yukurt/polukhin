#include <boost/mpl/aux_/na.hpp>

// boost::mpl::na == n.a. == not available
template <
	class T0 = boost::mpl::na,
	class T1 = boost::mpl::na,
	class T2 = boost::mpl::na,
	class T3 = boost::mpl::na,
	class T4 = boost::mpl::na,
	class T5 = boost::mpl::na,
	class T6 = boost::mpl::na,
	class T7 = boost::mpl::na,
	class T8 = boost::mpl::na,
	class T9 = boost::mpl::na
>
struct variant;

#include <boost/mpl/vector.hpp>

template <
	  class T0
	, class T1
	, class T2
	, class T3
	, class T4
	, class T5
	, class T6
	, class T7
	, class T8
	, class T9
>
struct variant {
	typedef boost::mpl::vector<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> types;
};

#include <string>

struct declared{ unsigned char data[4096]; };

struct non_defined;

typedef variant<
	volatile int,
	const int,
	const long,
	declared,
	non_defined,
	std::string
>::types types;

#include <boost/static_assert.hpp>
#include <boost/mpl/empty.hpp>
BOOST_STATIC_ASSERT((!boost::mpl::empty<types>::value));

#include <boost/mpl/at.hpp>
#include <boost/type_traits/is_same.hpp>
BOOST_STATIC_ASSERT((boost::is_same<
	  non_defined
	, boost::mpl::at_c<types, 4>::type>::value));

#include <boost/mpl/back.hpp>
BOOST_STATIC_ASSERT((boost::is_same<
	  std::string
	, boost::mpl::back<types>::type>::value));

#include <boost/mpl/transform.hpp>
#include <boost/type_traits/remove_cv.hpp>
typedef boost::mpl::transform<
	types,
	boost::remove_cv<boost::mpl::_1>
>::type noncv_types;

#include <boost/mpl/unique.hpp>
typedef boost::mpl::unique<
	noncv_types,
	boost::is_same<boost::mpl::_1, boost::mpl::_2>
>::type unique_types;

#include <boost/mpl/size.hpp>
BOOST_STATIC_ASSERT((boost::mpl::size<unique_types>::value == 5));

// Without this we'll get an error:
// use of undefined type 'non_defined'
struct non_defined{};

#include <boost/mpl/sizeof.hpp>
typedef boost::mpl::transform<
	unique_types,
	boost::mpl::sizeof_<boost::mpl::_1>
>::type sizes_types;

#include <boost/mpl/max_element.hpp>
typedef boost::mpl::max_element<sizes_types>::type max_size_type;

BOOST_STATIC_ASSERT(max_size_type::type::value == sizeof(declared));

int main()
{
	return 0;
}
