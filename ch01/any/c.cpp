#include <boost/any.hpp>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<boost::any> some_values;

    some_values.push_back(10);
    const char* c_str = "Hello there!";
    some_values.push_back(c_str);
    some_values.push_back(std::string("Wow!"));

    std::string& s = boost::any_cast<std::string&>(some_values.back());
    s += " That is great!\n";
    std::cout << s;

    // int x = boost::any_cast<int>(some_values.back()); // will throw exception

    int* s2 = boost::any_cast<int>(&some_values.back());
    if (s2)
    {
        std::cout << *s2;
    }
    else
    {
        std::cout << "any_cast failed" << std::endl;
    }

    return 0;
}

// output:
// Wow! That is great!
// any_cast failed
