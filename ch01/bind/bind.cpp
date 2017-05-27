// Example usage of boost::bind

/* Sample run output:
impl1:
2
4
6

impl2:
4
8
12
*/

#include <boost/bind.hpp>
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>

template <class T>
struct mul_2_func_obj: public std::unary_function<T, T>
{
    T operator()(T n1) const
    {
        return n1 + n1;
    }
};

template <class T>
void mul_2_impl1(std::vector<T>& values)
{
    std::transform(values.begin(), values.end(), values.begin(), mul_2_func_obj<T>());
}

template <class T>
void mul_2_impl2(std::vector<T>& values)
{
    std::transform(values.begin(), values.end(), values.begin(), boost::bind(std::plus<T>(), _1, _1));
}

int main()
{
    std::vector<int> vec = {1,2,3};

    mul_2_impl1(vec);
    std::cout << "impl1:" << std::endl;
    for (auto i: vec)
    {
        std::cout << i << std::endl;
    }

    mul_2_impl2(vec);
    std::cout << std::endl << "impl2:" << std::endl;
    for (auto i: vec)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
