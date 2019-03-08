/* g++ -std=c++14 overloading_operator_move_semantics.cpp -o bin/overloading_operator_move_semantics */

/*
 * Goal is to overload operator+ so that there are no unnecessary ctor and copy ctor calls.
 * Example auto a = a + b +100;
*/

#include <iostream>

#define _e_1_ 0
#define _e_2_ 0
#define _e_3_ 0
#define _e_4_ 0
#define _e_5_ 0
#define _e_6_ 1

struct X
{
		// default ctor
		X()
		{
			std::cout << "\tX::X()";
		}

		// ctor with type T
		X(const int& i) : i_(i)
		{
			std::cout << "\tX::X(const int& i) i_: " << i_ << std::endl;
		}

		// copy ctor
		X(const X& x) : i_(x.i_)
		{
			std::cout << "\tX::X(const X& x) i_: " << i_ << std::endl;
		}

		// move ctor
		X(X&& x) : i_(std::move(x.i_))
		{
			std::cout << "\tX::X(X&& x) i_: " << i_ << std::endl;
			x.i_ = -1;
		}

		// destructor
		~X()
		{
			std::cout << "\tX::~X() i_: " << i_ << std::endl;
		}

		// copy assigment operator
		X& operator=(const X& rhs)
		{
			std::cout << "\tX::operator=(const X& rhs) i_ old: " << i_;
			i_ = rhs.i_;
			std::cout << " i_ new: " << i_ << std::endl;

			return *this;
	 	}

		// move assigment operator
		X& operator=(X&& rhs)
		{
			std::cout << "\tX::operator=(X&& rhs) i_ old: " << i_;
			i_ = std::move(rhs.i_);
			std::cout << " i_ new: " << i_ << std::endl;

		 return *this;
	 	}

		// cannot be used if we want move semantics (here RVO)
		// unary operator+ accepting const lvalue reference
		/*X operator+(const X& rhs)
		{
			std::cout << "X::operator+(const X& rhs): i_ + rhs.i_ =  " << i_ + rhs.i_ << std::endl;
			return X(i_ + rhs.i_);
		}*/

		int  i_;
};

X operator+(const X& lhs, X&& rhs)
{
	std::cout << "\toperator+(const X& lhs, X&& rhs) - return std::move(rhs) " << rhs.i_ << " + " << lhs.i_ << std::endl;
	rhs.i_ += lhs.i_;
	return std::move(rhs);
}

// operator when lhs is rvalue reference and rhs is lvalue reference, then move is used.
X operator+(X&& lhs, const X& rhs)
{
	std::cout << "\toperator+(X&& lhs, const X& rhs) - return std::move(lhs) " << rhs.i_ << " + " << lhs.i_ << std::endl;
	lhs.i_ += rhs.i_;
	return std::move(lhs);
}

// operator when lhs is rvalue reference and rhs is lvalue reference, then move is used.
X operator+(X&& lhs, X&& rhs)
{
	std::cout << "\toperator+(X&& lhs, X&& rhs) - return std::move(lhs) " << rhs.i_ << " + " << lhs.i_ << std::endl;
	lhs.i_ += rhs.i_;
	return std::move(lhs);
}
// operator when lhs is rvalue reference and rhs is lvalue reference, then move is used.
X operator+(const X& lhs, const X& rhs)
{
	std::cout << "\toperator+(X&& lhs, X&& rhs) - return std::move(lhs) " << rhs.i_ << " + " << lhs.i_ << std::endl;
	return X(lhs.i_ + rhs.i_);
}

int main()
{
// (1)
#if _e_1_
	{
		std::cout << "(1) ### X x_sum = x_1 + x_2 ###" << std::endl;
		std::cout << "- constructor calls before sum:" << std::endl;
		X x_1(2);
		X x_2(4);

		std::cout << std::endl;
		std::cout << "- sum:" << std::endl;

		X x_sum = x_1 + x_2;

		std::cout << std::endl << "sum: " << x_sum.i_ << std::endl; // 6
		std::cout << std::endl;
		std::cout << "- destructor calls after sum is done:" << std::endl;
	}
#endif

// (2)
#if _e_2_
	{
		std::cout << std::endl;
		std::cout << "(2) ### X x_sum = x_1 + 100 ###" << std::endl;
		std::cout << "- constructor calls before sum:" << std::endl;
		X x_1(2);

		std::cout << std::endl;
		std::cout << "- sum:" << std::endl;

		X x_sum = x_1 + 100 ;

		std::cout << std::endl;
		std::cout << "- destructor calls after sum is done:" << std::endl;
	}
#endif

// (3)
#if _e_3_
	{
		std::cout << std::endl;
		std::cout << "(3) ### X x_sum = x_1 + 100 + 100 + x_2 ###" << std::endl;
		std::cout << "- constructor calls before sum:" << std::endl;
		X x_1(2);
		X x_2(4);

		std::cout << std::endl;
		std::cout << "- sum:" << std::endl;

		X x_sum = x_1 + 100 + 100 + x_2;

		std::cout << std::endl;
		std::cout << "- destructor calls after sum is done:" << std::endl;
	}
#endif

// (4)
#if _e_4_
	{
		std::cout << std::endl;
		std::cout << "(4) ### X x_sum = 100 + x_1 ###" << std::endl;
		X x_1(2);
		std::cout << std::endl;

		std::cout << "- sum:" << std::endl;

		X x_sum = 100 + x_1;

		std::cout << std::endl;
		std::cout << "- destructor calls after sum is done:" << std::endl;
	}
#endif

// (5)
#if _e_5_
	{
		std::cout << std::endl;
		std::cout << "(5) ### X x_sum = 100 + 100 ###" << std::endl;

		std::cout << std::endl;

		std::cout << "- sum:" << std::endl;

		X x_sum = 100 + 100; // only constructor gets called

		std::cout << std::endl;
		std::cout << "- destructor calls after sum is done:" << std::endl;
	}
#endif

// (6)
#if _e_6_
	{
		std::cout << std::endl;
		std::cout << "(6) ### X x_sum = (x_1 + 100) + 50 ###" << std::endl;
		std::cout << "- constructor calls before sum:" << std::endl;
		X x_1(2);

		std::cout << std::endl;
		std::cout << "- sum:" << std::endl;

		X&& x_sum = (x_1 + 100 )+ 50; // TODO test when returning ref &&
		//x_sum = x_sum + 10;

		std::cout << std::endl;
		std::cout << "- destructor calls after sum is done:" << std::endl;
	}
#endif


}
