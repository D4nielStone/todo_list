#include <gtest/gtest.h>
#include "elem/element.hpp"

using namespace bgui;
TEST(ElementTest, GetID) {
    element a, b, c, d("TagTest");

    // 1. Id tests (different elements may have different ids)
    EXPECT_EQ(a.get_id(), "#0");
    EXPECT_EQ(b.get_id(), "#1");
    EXPECT_EQ(c.get_id(), "#2");
    EXPECT_EQ(d.get_id(), "TagTest#3");
}

TEST(ElementTest, RequestSizeAndMode) {
    element elem;
    
    // 1. Reuqest Size Test (default mode is pixel)
    elem.request_size(150.f, 200.f);
    
    EXPECT_FLOAT_EQ(elem.requested_size()[0], 150.f);
    EXPECT_FLOAT_EQ(elem.requested_size()[1], 200.f);

    EXPECT_EQ(elem.get_requested_mode()[0], mode::pixel);
    EXPECT_EQ(elem.get_requested_mode()[1], mode::pixel);
    
    // 2. Test with percentual mode
    elem.request_width(mode::percent, 50.f);
    elem.request_height(mode::percent, 25.f);

    EXPECT_FLOAT_EQ(elem.requested_size()[0], 50.f);
    EXPECT_FLOAT_EQ(elem.requested_size()[1], 25.f);
    EXPECT_EQ(elem.get_requested_mode()[0], mode::percent);
    EXPECT_EQ(elem.get_requested_mode()[1], mode::percent);
}

TEST(ElementTest, FinalRectManipulation) {
    element elem;
    
    // 1. Manual final rect set
    elem.set_final_rect(10, 20, 100, 50);

    // 2. Verify getters
    EXPECT_EQ(elem.processed_x(), 10);
    EXPECT_EQ(elem.processed_y(), 20);
    EXPECT_EQ(elem.processed_width(), 100);
    EXPECT_EQ(elem.processed_height(), 50);

    EXPECT_EQ(elem.processed_position()[0], 10);
    EXPECT_EQ(elem.processed_size()[1], 50);
    EXPECT_EQ(elem.processed_rect()[3], 50); // height

    elem.set_position(5, 15);
    EXPECT_EQ(elem.processed_x(), 5);
    EXPECT_EQ(elem.processed_y(), 15);
    EXPECT_EQ(elem.processed_width(), 100);

    elem.set_final_size(80, 40);
    EXPECT_EQ(elem.processed_width(), 80);
    EXPECT_EQ(elem.processed_height(), 40);
    EXPECT_EQ(elem.processed_x(), 5);
}
const vec2i AVAILABLE_SIZE = {400, 300};

TEST(ElementTest, UpdateSizeCalculation) {
    element elem;

    // 1. Test pixel mode
    elem.request_size(100.f, 50.f);

    elem.update_size(AVAILABLE_SIZE); 
    
    EXPECT_EQ(elem.processed_width(), 100);
    EXPECT_EQ(elem.processed_height(), 50);

    // 2. Test percentual mode
    elem.request_width(mode::percent, 50.f);
    elem.request_height(mode::percent, 25.f);

    elem.update_size(AVAILABLE_SIZE);
    
    // 50% of 400 = 200
    EXPECT_EQ(elem.processed_width(), 200); 
    // 25% of 300 = 75
    EXPECT_EQ(elem.processed_height(), 75);

    // 3. Test match parent
    elem.request_width(mode::match_parent, 0.f);
    elem.request_height(mode::match_parent, 0.f);
    
    elem.update_size(AVAILABLE_SIZE);

    EXPECT_EQ(elem.processed_width(), 400); 
    EXPECT_EQ(elem.processed_height(), 300);

    // 4. Test percent and pixel
    elem.request_width(mode::percent, 10.f);
    elem.request_height(mode::pixel, 120.f);
    
    elem.update_size(AVAILABLE_SIZE);

    // 10% of 400 = 40
    EXPECT_EQ(elem.processed_width(), 40);
    EXPECT_EQ(elem.processed_height(), 120);

    // 5. Test padding and margin:
    // Paddings and Margins SHOULD NOT affect the content.
    elem.set_padding(10, 10, 10, 10); // L, T, R, B
    elem.set_margin(5, 5, 5, 5);     // L, T, R, B

    elem.request_size(50.f, 50.f); 
    elem.request_mode(mode::pixel, mode::pixel); 
    elem.update_size(AVAILABLE_SIZE);

    EXPECT_EQ(elem.processed_width(), 50);
    EXPECT_EQ(elem.processed_height(), 50);

    // 6. Test Stretched
    vec2i stretch_size = {150, 150};
    elem.request_size(1.f, 1.f);
    elem.request_mode(mode::stretch, mode::stretch);
    elem.update_size(stretch_size);
    
    EXPECT_EQ(elem.processed_width(), 150);
    EXPECT_EQ(elem.processed_height(), 150);
}