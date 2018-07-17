#include <tuple>
#include <vector>

#include "vec3.h"
#include "gtest/gtest.h"


class TestVec3_Sum : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, std::vector<float>>> {};
class TestVec3_Difference : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, std::vector<float>>> {};
class TestVec3_Multiplication : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, std::vector<float>>> {};
class TestVec3_Division : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, std::vector<float>>> {};
class TestVec3_CrossProduct : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, std::vector<float>>> {};

class TestVec3_MultiplicationWithScalar : public ::testing::TestWithParam<std::tuple<Vec3, float , std::vector<float>>> {};
class TestVec3_DivisionWithScalar : public ::testing::TestWithParam<std::tuple<Vec3, float, std::vector<float>>> {};

class TestVec3_DotProduct : public ::testing::TestWithParam<std::tuple<Vec3, Vec3, float>> {};

class TestVec3_Normalise : public ::testing::TestWithParam<std::tuple<Vec3, std::vector<float>>> {};
class TestVec3_SquaredLength : public ::testing::TestWithParam<std::tuple<Vec3, float>> {};
class TestVec3_Length : public ::testing::TestWithParam<std::tuple<Vec3, float>> {};


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
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{2.0f, 2.0f, 2.0f}),
        std::make_tuple(Vec3(1.5f, 1.5f, 1.5f), Vec3(1.5f, 1.5f, 1.5f), std::vector<float>{3.0f, 3.0f, 3.0f})
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

TEST_P(TestVec3_Sum, testVec3_sumEqual)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    v1 += v2;

    EXPECT_EQ(v1[0], expected_result[0]);
    EXPECT_EQ(v1[1], expected_result[1]);
    EXPECT_EQ(v1[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_difference, TestVec3_Difference, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{-1.0f, -1.0f, -1.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.5f, 1.5f, 1.5f), Vec3(1.5f, 1.5f, 1.5f), std::vector<float>{0.0f, 0.0f, 0.0f})
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

TEST_P(TestVec3_Difference, testVec3_differenceEqual)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    v1 -= v2;

    EXPECT_EQ(v1[0], expected_result[0]);
    EXPECT_EQ(v1[1], expected_result[1]);
    EXPECT_EQ(v1[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_multiplication, TestVec3_Multiplication, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3(1.5f, 1.5f, 1.5f), Vec3(1.5f, 1.5f, 1.5f), std::vector<float>{2.25f, 2.25f, 2.25f})
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

TEST_P(TestVec3_Multiplication, testVec3_multiplicationEqual)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    v1 *= v2;

    EXPECT_EQ(v1[0], expected_result[0]);
    EXPECT_EQ(v1[1], expected_result[1]);
    EXPECT_EQ(v1[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_division, TestVec3_Division, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3(2.0f, 2.0f, 2.0f), Vec3(2.0f, 2.0f, 2.0f), std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3(4.0f, 2.0f, 1.0f), Vec3(2.0f, 2.0f, 2.0f), std::vector<float>{2.0f, 1.0f, 0.5f}),
        std::make_tuple(Vec3(1.0f, 2.0f, 4.0f), Vec3(2.0f, 2.0f, 2.0f), std::vector<float>{0.5f, 1.0f, 2.0f})
));
TEST_P(TestVec3_Division, testVec3_division)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = v1 / v2;

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}

TEST_P(TestVec3_Division, testVec3_divisionEqual)
{
    auto v1 = std::get<0>(GetParam());
    auto v2 = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    v1 /= v2;

    EXPECT_EQ(v1[0], expected_result[0]);
    EXPECT_EQ(v1[1], expected_result[1]);
    EXPECT_EQ(v1[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_scalarMultiplication, TestVec3_MultiplicationWithScalar, ::testing::Values(
        std::make_tuple(Vec3{0.0f, 0.0f, 0.0f}, 0.0f, std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3{0.0f, 0.0f, 0.0f}, 1.0f, std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3{1.0f, 1.0f, 1.0f}, 0.0f, std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3{1.0f, 1.0f, 1.0f}, 1.0f, std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3{1.0f, 1.0f, 1.0f}, 2.0f, std::vector<float>{2.0f, 2.0f, 2.0f})
        ));

TEST_P(TestVec3_MultiplicationWithScalar, testVec3_scalarMultiplication)
{
    auto v = std::get<0>(GetParam());
    auto k = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = v * k;

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_scalarDivision, TestVec3_DivisionWithScalar, ::testing::Values(
        std::make_tuple(Vec3{0.0f, 0.0f, 0.0f}, 1.0f, std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3{1.0f, 1.0f, 1.0f}, 1.0f, std::vector<float>{1.0f, 1.0f, 1.0f}),
        std::make_tuple(Vec3{1.0f, 1.0f, 1.0f}, 2.0f, std::vector<float>{.5f, .5f, .5f})
));

TEST_P(TestVec3_DivisionWithScalar, testVec3_scalarDivision)
{
    auto v = std::get<0>(GetParam());
    auto k = std::get<1>(GetParam());

    auto expected_result = std::get<2>(GetParam());

    auto res = v / k;

    EXPECT_EQ(res[0], expected_result[0]);
    EXPECT_EQ(res[1], expected_result[1]);
    EXPECT_EQ(res[2], expected_result[2]);
}

INSTANTIATE_TEST_CASE_P(testVec3_dotproduct, TestVec3_DotProduct, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3{0.0f, 0.0f, 0.0f}, 0.0f),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), Vec3{0.0f, 0.0f, 0.0f}, 0.0f),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), Vec3{0.0f, 0.0f, 0.0f}, 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 1.0f), Vec3{0.0f, 0.0f, 0.0f}, 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3{1.0f, 0.0f, 0.0f}, 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3{0.0f, 1.0f, 0.0f}, 0.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3{0.0f, 0.0f, 1.0f}, 0.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3{1.0f, 0.0f, 0.0f}, 1.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3{0.0f, 1.0f, 0.0f}, 1.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3{0.0f, 0.0f, 1.0f}, 1.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), Vec3{1.0f, 1.0f, 1.0f}, 3.0f)
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
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 1.0f}),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, -1.0f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), std::vector<float>{1.0f, -1.0f, 0.0f})
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

INSTANTIATE_TEST_CASE_P(testVec3_squaredlength, TestVec3_SquaredLength, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), 1.0f),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), 1.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 1.0f), 1.0f),
        std::make_tuple(Vec3(0.0f, 1.0f, 1.0f), 2.0f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), 3.0f)
));
TEST_P(TestVec3_SquaredLength, testVec3_squaredlength)
{
    auto v = std::get<0>(GetParam());

    auto expected_result = std::get<1>(GetParam());

    EXPECT_EQ(v.squared_length(), expected_result);
}

INSTANTIATE_TEST_CASE_P(testVec3_length, TestVec3_Length, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), 0.0f),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), 1.0f),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), 1.0f),
        std::make_tuple(Vec3(0.0f, 0.0f, 1.0f), 1.0f),
        std::make_tuple(Vec3(0.0f, 1.0f, 1.0f), 1.4142135381698608f),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), 1.7320507764816284f)
        ));
TEST_P(TestVec3_Length, testVec3_length)
{
    auto v = std::get<0>(GetParam());

    auto expected_result = std::get<1>(GetParam());

    EXPECT_EQ(v.length(), expected_result);
}

INSTANTIATE_TEST_CASE_P(testVec3_normalize, TestVec3_Normalise, ::testing::Values(
        std::make_tuple(Vec3(0.0f, 0.0f, 0.0f), std::vector<float>{0.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(1.0f, 0.0f, 0.0f), std::vector<float>{1.0f, 0.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 1.0f, 0.0f), std::vector<float>{0.0f, 1.0f, 0.0f}),
        std::make_tuple(Vec3(0.0f, 0.0f, 1.0f), std::vector<float>{0.0f, 0.0f, 1.0f}),
        std::make_tuple(Vec3(0.0f, 1.0f, 1.0f), std::vector<float>{0.0f, 1/1.4142135381698608f, 1/1.4142135381698608f}),
        std::make_tuple(Vec3(1.0f, 0.0f, 1.0f), std::vector<float>{1/1.4142135381698608f, 0.0f, 1/1.4142135381698608f}),
        std::make_tuple(Vec3(1.0f, 1.0f, 1.0f), std::vector<float>{1/1.7320507764816284f, 1/1.7320507764816284f, 1/1.7320507764816284f})
        ));
TEST_P(TestVec3_Normalise, testVec3_normalize)
{
    auto v = std::get<0>(GetParam());

    auto expected_result = std::get<1>(GetParam());

    v.normalize();

    EXPECT_EQ(v[0], expected_result[0]);
    EXPECT_EQ(v[1], expected_result[1]);
    EXPECT_EQ(v[2], expected_result[2]);
}

TEST_P(TestVec3_Normalise, testVec3_unitvector)
{
    auto v = std::get<0>(GetParam());

    auto expected_result = std::get<1>(GetParam());

    auto n = unit_vector(v);

    EXPECT_EQ(n[0], expected_result[0]);
    EXPECT_EQ(n[1], expected_result[1]);
    EXPECT_EQ(n[2], expected_result[2]);
}

