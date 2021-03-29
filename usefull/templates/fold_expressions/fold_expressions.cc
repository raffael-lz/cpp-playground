#include <iostream>

// NEEDS c++17

template <typename ...T>
auto Sum(T... s)
{
    return (... + s); // ((s1+s2)+s3)...
}

// with initial values
template <typename ...T>
constexpr auto ProdPreInit(T... p) -> double
{
    return (2. / ... / static_cast<double>(p));
}

template <typename ...T>
auto ProdPostInit(T... p)
{
    return (static_cast<double>(p) / ... / 2.);
}

template <typename ...T>
auto IsAnd(T... expr)
{
    return (... && expr);
}

template <typename ...T>
auto IsOr(T... expr)
{
    return (... || expr);
}

int main()
{
    std::cout << "Sum(1,5,2): " <<  Sum(1,5,2) << std::endl;
    //std:::cout << "Sum(): " << Sum() << std::endl; // Compilation error
    std::cout << std::endl;
    std::cout << "ProdPreInit(4, 5,7): " << ProdPreInit(4,5,7) << std::endl;
    std::cout << "ProdPostInit(4, 5,7): " << ProdPostInit(4,5,7) << std::endl;
    std::cout << std::endl;
    std::cout << "IsAnd(): " << IsAnd() << std::endl;
    std::cout << "IsAnd(true, true): " << IsAnd(true, true) << std::endl;
    std::cout << "IsAnd(true, false, true): " << IsAnd(true, false, true) << std::endl;
    std::cout << std::endl;
    std::cout << "IsOr(): " << IsOr() << std::endl;
    std::cout << "IsOr(true, false): " << IsOr(true, false) << std::endl;
    std::cout << "IsOr(false, false, false): " << IsOr(false, false, false) << std::endl;
}
