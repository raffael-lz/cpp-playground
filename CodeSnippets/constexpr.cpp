/* ConstExpression vs Const */

/* g++ -std=c++14 constexpr.cpp   -o build/constexpr -D _error_ */

/*
 * declared in C++11.
 * when used with variables constexpr indicates a value that is known during compile time and is const.
 * when used with functions...
*/

int main()
{
    const auto c_size = 10;	    // fine
    constexpr auto cx_size = 10;    // fine

    int bla; // filled somewhere
    const auto c_bla = bla;	    // fine
    #if _error_
    constexpr auto cx_bla = bla;    // error: the value of ‘bla’ is not usable in a constant expression
    #endif
}
