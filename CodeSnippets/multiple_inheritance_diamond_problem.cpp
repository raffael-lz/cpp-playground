/* DIAMOND PROBLEM */

/*
 * Parent --> Child1 -->
 *                      \
 *                    Child3
 *                      /
 * Parent --> Child2 -->
 *
 *
 * Child3 has two indirect base classes from Parent. So a Child3 object has two different parent
 * base class subobjects. This leads to a problem because a reference to Parent class will result
 * ambigious.
 *
 *
 *      ----> Child1 ---->
 *    /                   \
 * Parent                Child3
 *    \                   /
 *      ----> Child2 ---->
 *
 * The Parent instances is shared in Child1 and Child2.
 * In C++ this is done with the virtual modifier when inheriting from the class.
*/

#include <iostream>

struct Parent
{
	virtual void sit() {std::cout << "Parent::sit()" << std::endl; }
};

struct Child1 : Parent
{
	virtual void run() { std::cout << "Child1::run()" << std::endl; }
};

struct Child2 : Parent
{
	virtual void jump() { std::cout << "Child2::jump()" << std::endl; }
};

struct ComposedChild3 : Child1, Child2
{

};

/* Solution */
struct Child4 : virtual Parent
{
	virtual void run() { std::cout << "Child4::run()" << std::endl; }
};

struct Child5 : virtual Parent
{
	virtual void jump() { std::cout << "Child5::jump()" << std::endl; }
};

struct ComposedChild6 : Child4, Child5
{

};


int main()
{
	ComposedChild3 cc3;

	// Parent &p1 = cc3; // error: ‘Parent’ is an ambiguous base of ‘Child3’

	// Cast to either Child1 or Child2
	Parent &pc1 = static_cast<Child1&> (cc3);
	Parent &pc2 = static_cast<Child2&> (cc3);

	// c3.sit(); error: request for member ‘sit’ is ambiguous
	static_cast<Child1&>(cc3).sit();
	static_cast<Child2&>(cc3).sit();

	/* Solution */
	ComposedChild6 cc6;
	Parent &p2 = cc6;
	cc6.sit();
}
