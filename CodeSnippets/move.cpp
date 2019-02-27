/* */

/* */

/*
 * Replace expensive copy semantics.
 * Thanks to move std::unique_ptr, std::thread are possible (move only types).
 * 
*/

#include <iostream>

// (1)
#define S1

// move operator from Scott Meyers
template <typename T>
decltype(auto) move(T&& param)
{
    using ReturnType = typename std::remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

//template <typename T>
//typename std::remove_reference<T>::type&& move(T&& param)
//{
//    using ReturnType = typename std::remove_reference<T>::type&&;
//    return static_cast<ReturnType>(param);
//    //return static_cast<typename std::remove_reference<T>::type&&>(param);
//}

// (2)
#define S2

// wrong example from Scott Meyers
class Annotation
{
    public:
    explicit Annotation(const std::string text) : value(std::move(text))
    {}

    private:
    std::string value;
};


// (3)

struct X
{
};

X foobar()
{
    X x;
    return x;
}

void foo(X& x)
{
    std::cout << "lvalue reference" << std::endl;
}

void foo(X&& x)
{
    std::cout << "rvalue reference" << std::endl;
}

void foo(const X& x)
{
    std::cout << "const lvalue reference" << std::endl;
}

int main()
{
    // (1)
#ifdef S1
    {
	int* i_1 = new int(10);
	int* i_2 = move(i_1);
	
	std::cout << "(1)" << std::endl;
	if (i_1 != nullptr) // i_1 should now be null
	    std::cout << "I am null" << std::endl;
	std::cout << *i_2 << std::endl;
    }
#endif

#ifdef S2
    {
	std::string s_1 = "Hallo";
	Annotation a(s_1);
	std::cout << "s_1: " << std::endl;
    }
#endif

    {
	X x;
	foo(x);
	foo(foobar());
    }

}
