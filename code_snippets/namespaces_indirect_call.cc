#include <iostream>
#include <string>

namespace foo
{
class Test
{
};

void f1() { std::cout << "f1() called" << std::endl; }

void f11(Test t) { std::cout << "f11 called" << std::endl; }

bool operator==(const Test &t, const std::string &s)
{
  std::cout << "operator== called" << std::endl;
  return true;
}
} // namespace foo

void indirect_call(foo::Test t, std::string s)
{
  // f1(); // undeclared identifier f1

  f11(t); // gets called

  if (t == s) {}
}

int main()
{
  foo::Test t;
  indirect_call(t, "hallo");
}
