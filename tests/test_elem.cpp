#include <gtest/gtest.h>
#include "elem/element.hpp"

TEST(ElementTest, Id) {
    bgui::element a, b, c, d("TagTest");
    EXPECT_EQ(a.get(), "#0");
    EXPECT_EQ(b.get(), "#1");
    EXPECT_EQ(c.get(), "#2");
    EXPECT_EQ(d.get(), "TagTest#3");
}