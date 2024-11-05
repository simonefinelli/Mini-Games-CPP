#include "gtest/gtest.h"
#include "Vec2D.h"

// Basic functionality tests ================================================ //

// Test default constructor and getters
TEST(Vec2DTest, DefaultConstructor) {
    Vec2D vec;
    EXPECT_EQ(vec.get_x(), 0);
    EXPECT_EQ(vec.get_y(), 0);
}

// Test custom constructor and getters
TEST(Vec2DTest, CustomConstructor) {
    Vec2D vec(3.0f, 4.0f);
    EXPECT_EQ(vec.get_x(), 3.0f);
    EXPECT_EQ(vec.get_y(), 4.0f);
}

// Test Setters.
TEST(Vec2DTest, Setters) {
    Vec2D vec;
    vec.set_x(5.3f);
    vec.set_y(6.89f);
    EXPECT_EQ(vec.get_x(), 5.3f);
    EXPECT_EQ(vec.get_y(), 6.89f);
}


// Arithmetic operations ==================================================== //

// Test vector addition
TEST(Vec2DTest, Addition) {
    Vec2D vec1(1.0f, 2.0f);
    Vec2D vec2(2.0f, 3.0f);
    Vec2D result = vec1 + vec2;
    
    EXPECT_EQ(result.get_x(), 3.0f);
    EXPECT_EQ(result.get_y(), 5.0f);
}

// Test vector subtraction
TEST(Vec2DTest, Subtraction) {
    Vec2D vec1(4.0f, 5.0f);
    Vec2D vec2(1.0f, 1.0f);
    Vec2D result = vec1 - vec2;

    EXPECT_EQ(result.get_x(), 3.0f);
    EXPECT_EQ(result.get_y(), 4.0f);
}

// Test scalar multiplication
TEST(Vec2DTest, ScalarMultiplication) {
    Vec2D vec(2.0f, 3.0f);
    Vec2D result = vec * 2.0f;

    EXPECT_EQ(result.get_x(), 4.0f);
    EXPECT_EQ(result.get_y(), 6.0f);
}

// Test scalar division and zero-division
TEST(Vec2DTest, ScalarDivision) {
    Vec2D vec(6.0f, 8.0f);
    Vec2D result = vec / 2.0f;

    EXPECT_EQ(result.get_x(), 3.0f);
    EXPECT_EQ(result.get_y(), 4.0f);

    // Test division by zero (or very small float number)
    EXPECT_THROW(vec / 0.0f, std::runtime_error);
    EXPECT_THROW(vec / 0.0000000001f, std::runtime_error);
}



// Special operations ======================================================= //

// Test vector magnitude
TEST(Vec2DTest, Magnitude) {
    Vec2D vec(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(vec.mag(), 5.0f);
}

// Test vector normalization
TEST(Vec2DTest, Normalization) {
    Vec2D vec(3.0f, 4.0f);
    Vec2D unit_vec = vec.get_unit_vec();

    EXPECT_FLOAT_EQ(unit_vec.mag(), 1.0f);
    EXPECT_FLOAT_EQ(unit_vec.get_x(), 3.0f / 5.0f);
    EXPECT_FLOAT_EQ(unit_vec.get_y(), 4.0f / 5.0f);
}

// Test dot product
TEST(Vec2DTest, DotProduct) {
    Vec2D vec1(1.0f, 2.0f);
    Vec2D vec2(2.0f, 3.0f);
    
    EXPECT_FLOAT_EQ(vec1.dot(vec2), 8.0f);  // 1*2 + 2*3 = 8
}

// Test projection onto another vector
TEST(Vec2DTest, Projection) {
    Vec2D vec1(3.0f, 4.0f);
    Vec2D vec2(1.0f, 0.0f);

    Vec2D projected = vec1.project_onto(vec2);
    EXPECT_FLOAT_EQ(projected.get_x(), 3.0f);
    EXPECT_FLOAT_EQ(projected.get_y(), 0.0f);
}

// Test rotation
TEST(Vec2DTest, Rotation) {
    Vec2D vec(1.0f, 0.0f);
    Vec2D rotated = vec.rotation_result(M_PI / 2);  // 90 degrees rotation
    
    EXPECT_NEAR(rotated.get_x(), 0.0f, 1e-5);  // x should be close to 0
    EXPECT_NEAR(rotated.get_y(), 1.0f, 1e-5);  // y should be 1
}

// Test reflection
TEST(Vec2DTest, Reflection) {
    Vec2D vec(1.0f, 1.0f);
    Vec2D normal(1.0f, 0.0f);
    
    Vec2D reflected = vec.reflect(normal);
    EXPECT_FLOAT_EQ(reflected.get_x(), -1.0f);
    EXPECT_FLOAT_EQ(reflected.get_y(), 1.0f);
}


// Edge and corner cases ==================================================== //

// Test normalization of a zero vector
TEST(Vec2DTest, NormalizeZeroVector) {
    Vec2D vec;
    Vec2D unit_vec = vec.get_unit_vec();

    EXPECT_EQ(unit_vec, Vec2D::ZERO);  // normalization of zero vector should return zero vector
}




