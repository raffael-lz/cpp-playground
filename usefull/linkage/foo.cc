#include <iostream>

#include "foo.h"

// internal linkage, not visible in other translation unit
constexpr int kGlobalConstExpr{5}; // same variable name in bar.cc
const int kGlobalConst{1};         // same variable name in bar.cc

int GetFooConstexpr() { return kGlobalConstExpr; }
int GetFooConst() { return kGlobalConst; }

// use of a function of bar without including bar.h
int FuncBar(); // forward declaration, linked later to linkage_b.cc::f()

void FuncFoo() { std::cout << "Value of FuncBar: " << FuncBar() << std::endl; }
