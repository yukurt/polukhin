#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    typedef boost::variant<int, const char*, std::string>
    my_var_t;
    std::vector<my_var_t> some_values;
    some_values.push_back(10);
    some_values.push_back("Hello there!");
    some_values.push_back(std::string("Wow!"));
    std::string& s = boost::get<std::string>(some_values.back());
    s += " That is great!\n";
    std::cout << s;

    typedef boost::variant<boost::blank, int, const char*, std::string> my_var_t2;
    // Default constructor will construct an
    // instance of boost::blank
    my_var_t2 var;
    // 'which()' method returns an index of a type,
    // currently held by variant.
    assert(var.which() == 0); // Empty state
    var = "Hello, dear reader";
    assert(var.which() != 0);

    boost::variant<int, std::string> variable("hello");
    // Following method may throw a boost::bad_get
    // exception if actual value in variable is not an int
    // int s1 = boost::get<int>(variable);
    std::string s1 = boost::get<std::string>(variable);
    std::cout << s1 << std::endl;

    // If actual value in variable is not an int
    // will return an NULL pointer
    int* s2 = boost::get<int>(&variable);
    if (s2)
    {
        std::cout << s2 << std::endl;
    }
    else
    {
        std::cout << "s2 is null" << std::endl;
    }

    return 0;
}

/* output
Wow! That is great!
hello
s2 is null
*/
