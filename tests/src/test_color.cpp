#include <tuple>
#include <vector>

#include "color.h"
#include "vec3.h"
#include "gtest/gtest.h"


TEST(TestColor, color_init_zero)
{
    auto c = Color();

    EXPECT_EQ(c.r(), 0.0f);
    EXPECT_EQ(c.g(), 0.0f);
    EXPECT_EQ(c.b(), 0.0f);
}

class TestColor_InitValues : public ::testing::TestWithParam<std::tuple<Color, std::vector<float>>> {};

INSTANTIATE_TEST_CASE_P(color_init_value, TestColor_InitValues, ::testing::Values(
        std::make_tuple(Color(0, 0, 0), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Color(255, 0, 0), std::vector<float>{1.0f, 0.0f, 0.0f}),
        std::make_tuple(Color(0, 255, 0), std::vector<float>{0.0f, 1.0f, 0.0f}),
        std::make_tuple(Color(0, 0, 255), std::vector<float>{0.0f, 0.0f, 1.0f}),
        std::make_tuple(Color(255, 255, 255), std::vector<float>{1.0f, 1.0f, 1.0f})
        ));

TEST_P(TestColor_InitValues, color_init_values)
{
    auto c = std::get<0>(GetParam());

    auto expected_result = std::get<1>(GetParam());

    EXPECT_EQ(c.r(), expected_result[0]);
    EXPECT_EQ(c.g(), expected_result[1]);
    EXPECT_EQ(c.b(), expected_result[2]);
}

class TestColor_InitFromVec3 : public ::testing::TestWithParam<std::tuple<Vec3, std::vector<float>>> {};

INSTANTIATE_TEST_CASE_P(Color_init_from_vec3, TestColor_InitFromVec3, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), std::vector<float>{1.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), std::vector<float>{0.0f, 1.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 0.0f, 1.0f), std::vector<float>{0.0f, 0.0f, 1.0f})
        ));

TEST_P(TestColor_InitFromVec3, Color_init_from_vec3)
{
    auto c = Color(std::get<0>(GetParam()));

    auto expected_result = std::get<1>(GetParam());

    EXPECT_EQ(c.r(), expected_result[0]);
    EXPECT_EQ(c.g(), expected_result[1]);
    EXPECT_EQ(c.b(), expected_result[2]);
}