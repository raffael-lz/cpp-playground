#include <string>

template <typename T> struct Property {
  T value_;

  Property(T value) : value_(value) {}

  T operator=(const T &value) { return value_ = value; }

  operator T() const { return value_; }
};

struct Monster {
  Property<std::string> name_{"Bad guy"};
  Property<int> level_{8};
  Property<float> bla_{8.0f};
};

int main() {
  Monster m;
  m.name_ = "Good Guy";
}
