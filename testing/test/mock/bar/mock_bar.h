#include "bar/bar.h"

#include "gmock/gmock.h"

class MockBar : public Bar
{
  public:
    explicit MockBar() = default;
    virtual ~MockBar() = default;
    MOCK_METHOD(void, Update, (), (override));
    MOCK_METHOD(void, SetSomething, (const int s), (override));
    MOCK_METHOD(int, GetSomething, (), (const, override));
};
