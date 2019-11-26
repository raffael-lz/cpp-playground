#include <iostream>
#include <string>

/*
 * (1) adds namespace bar to the globale scope, but local scope (foo) has
 * priority -> error (2) adds bar::f to scope of foo. so know bar::f and foo::f
 * are in the same scope -> works (3) adds bar::f to scope of foo:g. Hides then
 * foo:f. Need to add also using foo:f (3.1) (4) scope is global, but local
 * scope has priority. Does locate foo::f and throws then error
 */

namespace bar
{
void f(float a) { std::cout << "bar::f" << std::endl; }
} // namespace bar

namespace foo
{
// using namespace bar; // does not find bar::f(float) (1)
using bar::f; // this works (2)
void f(std::string a) { std::cout << "foo:f" << std::endl; }

void g()
{
    //  using bar::f; // does not find foo::f(std::string) (3)
    //  using foo::f; // works with (3) togehter (3.1)
    //  using namespace bar; // does not find bar::f(float) from bar (4)
    f(std::string{"t"}); // should call foo:f
    f(2.0f);             // should call bar:f
}
} // namespace foo

int main() { foo::g(); }
