#include "bar.h"

// internal linkage, not visible in other translation unit
constexpr int kGlobalConstExpr{10}; // same variable name in foo.cc
const int kGlobalConst{2};          // same variable name in foo.cc

int GetBarConstexpr() { return kGlobalConstExpr; }
int GetBarConst() { return kGlobalConst; }

int FuncBar() { return kGlobalConstExpr; }
