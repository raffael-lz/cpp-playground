/*
 - have a class with methods having same signature. they can perform some checks
 and will return a boolean.
*/

#include <array>

struct MethodCollector
{
    bool IsA() const { return false; }
    bool IsB() const { return true; }
    bool IsC() const { return false; }
    bool IsD() const { return true; }
    bool IsE() const { return true; }
};

struct MethodAction
{
    std::function<bool(const MethodCollector)> method;
    int action;
};

const std::array<MethodAction, 1> kFirstGroup = {{&MethodCollector::IsA, 2}};

void DoSomething() {}

int main() {}
