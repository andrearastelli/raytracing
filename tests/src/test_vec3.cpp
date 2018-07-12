#include "vec3.h"
#include "gtest/gtest.h"


class TestVec3 : public ::testing::TestWithParam<Vec3>
{
public:
    void SetUp() override {}
    void TearDown() override {}
};


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

TEST(test_vec3, vec3_sum)
{
    auto v1 = Vec3();
    auto v2 = Vec3(1.0f, 0.0f, 1.0f);

    auto v3 = v1 + v2;

    EXPECT_EQ(v3[0], 1.0f);
    EXPECT_EQ(v3[1], 0.0f);
    EXPECT_EQ(v3[2], 1.0f);
}

TEST(test_vec3, vec3_difference)
{
    auto v1 = Vec3();
    auto v2 = Vec3(1.0f, 0.0f, 1.0f);

    auto v3 = v1 - v2;

    EXPECT_EQ(v3[0], -1.0f);
    EXPECT_EQ(v3[1], 0.0f);
    EXPECT_EQ(v3[2], -1.0f);
}

TEST(test_vec3, vec3_multiplication)
{
    auto v1 = Vec3();
    auto v2 = Vec3(1.0f, 0.0f, 1.0f);

    auto v3 = v1 * v2;

    EXPECT_EQ(v3[0], 0.0f);
    EXPECT_EQ(v3[1], 0.0f);
    EXPECT_EQ(v3[2], 0.0f);
}

auto dot_product_values = ::testing::Values(
        Vec3(1.0f, 1.0f, 1.0f)
);

INSTANTIATE_TEST_CASE_P(test_vec3, TestVec3, dot_product_values);
TEST_P(TestVec3, vec3_dot_product)
{
    auto v1 = Vec3();
    auto v2 = Vec3(1.0f, 1.0f, 1.0f);

    auto res = dot(v1, v2);

    EXPECT_EQ(res, 0.0f);
}

