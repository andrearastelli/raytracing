#include <tuple>

#include "vec3.h"
#include "gtest/gtest.h"


class TestVec3_Sum : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, Vec3>> {};
class TestVec3_Difference : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, Vec3>> {};
class TestVec3_Multiplication : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, Vec3>> {};
class TestVec3_Division : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, Vec3>> {};
class TestVec3_CrossProduct : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, Vec3>> {};

class TestVec3_DotProduct : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, float>> {};


TEST(test_vec3, vec3_init_zero)
{
    auto v = Vec3();

    EXPECT_EQ(v[0], .0f);
    EXPECT_EQ(v[1], .0f);
    EXPECT_EQ(v[2], .0f);
}

TEST(test_vec3, vec3_init_xyz)
{
    auto v = Vec3(1.0f, 1.0f, 1.0f);

    EXPECT_EQ(v[0], 1.0f);
    EXPECT_EQ(v[1], 1.0f);
    EXPECT_EQ(v[2], 1.0f);
}

INSTANTIATE_TEST_CASE_P(testVec3_sum, TestVec3_Sum, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f)),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(2.0f, 2.0f, 2.0f)),
        std::make_tuple(Vec3(1.5f, 1.5f, 1.5f), Vec3(1.5f, 1.5f, 1.5f), Vec3(3.0f, 3.0f, 3.0f))
));
TEST_P(TestVec3_Sum, testVec3_sum)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = v1 + v2;

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}


INSTANTIATE_TEST_CASE_P(testVec3_difference, TestVec3_Difference, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(-1.0f, -1.0f, -1.0f)),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(1.5f, 1.5f, 1.5f), Vec3(1.5f, 1.5f, 1.5f), Vec3(0.0f, 0.0f, 0.0f))
));
TEST_P(TestVec3_Difference, testVec3_difference)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = v1 - v2;

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}


INSTANTIATE_TEST_CASE_P(testVec3_multiplication, TestVec3_Multiplication, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f)),
        std::make_tuple(Vec3(1.5f, 1.5f, 1.5f), Vec3(1.5f, 1.5f, 1.5f), Vec3(2.25f, 2.25f, 2.25f))
));
TEST_P(TestVec3_Multiplication, testVec3_multiplication)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = v1 * v2;

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_dotproduct, TestVec3_DotProduct, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), 0.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), 1.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), 1.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), 1.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), 3.0f)
        //std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), 1.0f)
        ));
TEST_P(TestVec3_DotProduct, testVec3_dotproduct)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = dot(v1, v2);

    EXPECT_EQ(res, expected_result);
}

INSTANTIATE_TEST_CASE_P(testVec3_crossproduct, TestVec3_CrossProduct, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f)),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f))
        ));
TEST_P(TestVec3_CrossProduct, testVec3_crossproduct)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = cross(v1, v2);

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}