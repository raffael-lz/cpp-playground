#include "foo/foo.h"
#include "mock/bar/mock_bar.h"

#include "gtest/gtest.h"

TEST(FooTest, test1)
{
    MockBar mock_bar;
    Foo f;
    EXPECT_TRUE(false);
}
