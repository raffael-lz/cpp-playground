size = 200;

f = open("test_not_optimal.cc", "w")

headers = """#include <iostream>
"""

declaration_foo = """
template <typename T> struct Foo {
  void Calculate();
  void DoSomething() const;
  void DoNothing() const;
  int a{2};
  int b{9};
  T tt;
};
"""

definition_foo = """
template <typename T> void Foo<T>::Calculate() {
  DoSomething();

  if ((a + b) < 10) {
    DoNothing();
  }

  std::cout << static_cast<int>(tt);
}

template <typename T> void Foo<T>::DoSomething() const {
  std::cout << "DoSomething()" << std::endl;
}

template <typename T> void Foo<T>::DoNothing() const {
  std::cout << "DoNothing()" << std::endl;
}
"""

enums = "";
for i in range(size):
    enums += "enum class A" + str(i) +" { a, b, c, d };\n"

main = """
int main() {
"""

for i in range(size):
    main += "Foo<A"+str(i)+"> foo"+str(i)+";\n";

for i in range(size):
    main += "foo"+str(i)+".Calculate();\n";

main +="}"
output = headers + declaration_foo + definition_foo + enums + main
f.write(output)
f.close()
