/* ConstExpression vs Const */

/* g++ -std=c++11 constexpr.cpp   -o bin/constexpr -D _error_ */

/*
 * Declared in C++11.
 * When used with variables constexpr indicates a value that is known during compile time and is const. (1)
 * when used with functions...
*/

int main()
{
// (1)
	const auto c_size = 10;	        // fine
	constexpr auto cx_size = 10;    // fine

	int bla;                    // filled somewhere
	const auto c_bla = bla;	    // fine
#if _error_
	constexpr auto cx_bla = bla;    // error: the value of ‘bla’ is not usable in a constant expression
#endif
}
