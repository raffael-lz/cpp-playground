/* */

/* g++ -std=c++14 -pthread templates.cpp -o bin/templates */

/*
 * ... can expand a whole parameter pack containing functions calls, see (2)
 *
 *
*/

#include <iostream>

// (1)
/* Variadict template */

// Base function 
template <typename T>
decltype(auto) Sum(T t)
{
    return t;
}

// Recursive variadic template
template <typename T, typename... Args>
decltype(auto) Sum(T t, Args... args)
{
   return t + Sum(args...);
}

// more complicated (http://kevinushey.github.io/blog/2016/01/27/introduction-to-c++-variadic-templates/)
// (2)
template <typename T>
T Square(T t)
{
    return t*t;
}

template <typename T>
T Pow(T t)
{
    return t;
}

template <typename T, typename... TArgs>
decltype(auto) Pow(T t, TArgs... args)
{
    return t + Pow(Square(args)...);
    // Pow(2, 4, 6);
    // 2 + Pow(Square(4) , Square(6));
    // 2 + Square(4) + Pow(Square(Square(6)));
    // 2 + Square(4) + Square(Square(6));
}

// https://florianjw.de/en/variadic_templates.html

template<typename...Ts>
void ignore_returnvalues(Ts&&...) {}

template<typename... Iterators>
void increment_all(Iterators&... its) {
	ignore_returnvalues((++its)...);


int main()
{
    // (1)
    int sum_int = Sum(1,3,5,7);
    float sum_float = Sum(1.0, 2, 1.0, 4.3);
    std::cout << "sum_int: " << sum_int << std::endl;
    std::cout << "sum_float: " << sum_float << std::endl;

    float pow_float = Pow(2.0,2,4);
    std::cout << "pow_float: " << pow_float << std::endl;
}
