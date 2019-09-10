#include <functional>
#include <iostream>
#include <string>

class Logger_1 {
  std::function<void()> func_;
  std::string name_;

public:
  Logger_1(const std::function<void()> &func, const std::string &name)
      : func_(func), name_(name) {}

  void operator()() const {
    std::cout << "Enter: " << name_ << std::endl;
    func_();
    std::cout << "Exit: " << name_ << std::endl;
  }
};

void func_1() { std::cout << "Hello" << std::endl; }

template <typename Func> class Logger_2 {
public:
  Logger_2(const Func &func, const std::string &name)
      : func_(func), name_(name) {}

  void operator()() const {
    std::cout << "Enter_2: " << name_ << std::endl;
    func_();
    std::cout << "Exit_2: " << name_ << std::endl;
  }

private:
  Func func_;
  std::string name_;
};

template <typename Func>
auto make_shared_2(const Func &func, const std::string &name) {
  return Logger_2<Func>(func, name);
}

struct Logger_3 {
  std::function<double(double, double)> func_;
  std::string name_;

  Logger_3(const std::function<double(double, double)> &func,
           const std::string name)
      : func_(func), name_(name) {}

  void operator()() {
    std::cout << "Logger_3: enter " << name_ << std::endl;
    std::cout << "result: " << func_(1.0, 2.0) << std::endl;
    std::cout << "Logger_3: exit " << name_ << std::endl;
  }
};

auto make_shared_3(const std::function<double(double, double)> &func,
                   const std::string &name) {
  return Logger_3(func, name);
}

double multiply(double a, double b) { return a * b; }

int main() {
  Logger_1([]() { std::cout << "bla" << std::endl; }, "Test")();
  Logger_1(func_1, "func_1")();

  auto log2 = make_shared_2([]() { std::cout << "bla" << std::endl; }, "Test");
  log2();

  auto log3 = make_shared_3(multiply, "Test_3");
  log3();
}
