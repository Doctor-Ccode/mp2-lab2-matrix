#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(3);
  m[1][1]=7;
  TDynamicMatrix<int> c(m);
  EXPECT_TRUE(c==m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 42;

  TDynamicMatrix<int> m1(m);
  m1[0][0] = 7;

  EXPECT_EQ(m[0][0], 42);
  EXPECT_EQ(m1[0][0], 7);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(2);

  EXPECT_EQ(2, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 5;

  EXPECT_EQ(5, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);

  EXPECT_THROW(m.at(static_cast<size_t>(-2)), std::out_of_range);

  EXPECT_THROW(m[2].at(static_cast<size_t>(-1)), std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);

  EXPECT_THROW(m.at(3), std::out_of_range);

  EXPECT_THROW(m[2].at(3), std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 1;

  m = m;

  EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(3), b(3);
  a[0][0] = 1;
  b[0][0] = 5;

  a = b;

  EXPECT_EQ(5, a[0][0]);
  EXPECT_EQ(3, a.size());
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> a(3), b(5);

  a = b;

  EXPECT_EQ(5, a.size());

}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> a(3), b(4);
  b[3][3] = 11;

  a = b;

  EXPECT_EQ(4, a.size());
  EXPECT_EQ(11, a[3][3]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;

  EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(2);

  EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(2), b(3);

  EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 10; b[0][1] = 20; b[1][0] = 30; b[1][1] = 40;

  TDynamicMatrix<int> c = a + b;

  EXPECT_EQ(11, c[0][0]);
  EXPECT_EQ(22, c[0][1]);
  EXPECT_EQ(33, c[1][0]);
  EXPECT_EQ(44, c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);

  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 10; a[0][1] = 20; a[1][0] = 30; a[1][1] = 40;
  b[0][0] = 1;  b[0][1] = 2;  b[1][0] = 3;  b[1][1] = 4;

  TDynamicMatrix<int> c = a - b;

  EXPECT_EQ(9,  c[0][0]);
  EXPECT_EQ(18, c[0][1]);
  EXPECT_EQ(27, c[1][0]);
  EXPECT_EQ(36, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);

  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;

  TDynamicMatrix<int> c = a * b;

  // [1*5+2*7=19, 1*6+2*8=22; 3*5+4*7=43, 3*6+4*8=50]
  EXPECT_EQ(19, c[0][0]);
  EXPECT_EQ(22, c[0][1]);
  EXPECT_EQ(43, c[1][0]);
  EXPECT_EQ(50, c[1][1]);
}

