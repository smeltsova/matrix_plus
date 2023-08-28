#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(DefaultConstructor, Subtest_1) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);

  EXPECT_EQ(matrix(0, 0), 0);
  EXPECT_EQ(matrix(1, 1), 0);
  EXPECT_EQ(matrix(2, 2), 0);
  EXPECT_ANY_THROW(matrix(3, 3));
}

TEST(ParameterizedConstructor, Subtest_1) {
  S21Matrix matrix(15, 20);
  EXPECT_EQ(matrix.GetRows(), 15);
  EXPECT_EQ(matrix.GetCols(), 20);
}

TEST(ParameterizedConstructor, Subtest_2) {
  EXPECT_ANY_THROW(S21Matrix empty_matrix(0, 0));
}

TEST(ParameterizedConstructor, Subtest_3) {
  EXPECT_ANY_THROW(S21Matrix negative_matrix(-2, -3));
  EXPECT_ANY_THROW(S21Matrix negative_matrix(3, -1));
  EXPECT_ANY_THROW(S21Matrix negative_matrix(-2, 5));
}

TEST(CopyConstructor, Subtest_1) {
  S21Matrix first;
  first(0, 0) = 324;
  first(1, 0) = 87;
  first(2, 0) = -43;
  first(0, 1) = 3;
  first(1, 1) = 8;
  first(2, 1) = 9843;
  first(0, 2) = -324;
  first(1, 2) = 8786;
  first(2, 2) = -98;

  S21Matrix second(first);
  EXPECT_EQ(first.EqMatrix(second), true);

  S21Matrix third = first;
  EXPECT_EQ(first.EqMatrix(third), true);
}

TEST(CopyConstructor, Subtest_2) {
  S21Matrix first(1, 2);
  first(0, 0) = 324;
  first(0, 1) = -3;

  S21Matrix second(first);
  EXPECT_EQ(first.EqMatrix(second), true);
}

TEST(MoveConstructor, Subtest_1) {
  S21Matrix first;
  first(0, 0) = 324;
  first(1, 0) = 87;
  first(2, 0) = -43;
  first(0, 1) = 3;
  first(1, 1) = 8;
  first(2, 1) = 9843;
  first(0, 2) = -324;
  first(1, 2) = 8786;
  first(2, 2) = -98;

  S21Matrix second(first);
  S21Matrix third(std::move(first));

  EXPECT_EQ(third.EqMatrix(second), true);
  EXPECT_EQ(third.EqMatrix(first), false);
  EXPECT_ANY_THROW(first(0, 0));
}

TEST(MoveConstructor, Subtest_2) {
  S21Matrix first;
  first(0, 0) = 324;
  first(1, 0) = 87;
  first(2, 0) = -43;
  first(0, 1) = 3;
  first(1, 1) = 8;
  first(2, 1) = 9843;
  first(0, 2) = -324;
  first(1, 2) = 8786;
  first(2, 2) = -98;

  S21Matrix second(first);
  S21Matrix third(std::move(first));

  EXPECT_EQ(third.EqMatrix(second), true);
  EXPECT_EQ(third.EqMatrix(first), false);
  EXPECT_ANY_THROW(first(0, 0));
}

TEST(EqMatrix, Subtest_1) {
  S21Matrix first(2, 5), second(2, 5);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      first(i, j) = 5 * i + j;
      second(i, j) = 5 * i + j;
    }
  }
  EXPECT_EQ(first.EqMatrix(second), true);
}

TEST(EqMatrix, Subtest_2) {
  S21Matrix first(2, 5), second(3, 5);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      first(i, j) = 5 * i + j;
      second(i, j) = 5 * i + j;
    }
  }
  EXPECT_EQ(first.EqMatrix(second), false);
}

TEST(EqMatrix, Subtest_3) {
  S21Matrix first(3, 2), second(3, 5);
  EXPECT_EQ(first.EqMatrix(second), false);
}

TEST(EqMatrix, Subtest_4) {
  S21Matrix first(2, 5), second(2, 5);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      first(i, j) = 5 * i + j;
      second(i, j) = 5 * i + j;
    }
  }
  first(0, 0) += 0.99 * S21_MATRIX_OOP_EPS;
  EXPECT_EQ(first.EqMatrix(second), true);

  first(1, 1) += 2 * S21_MATRIX_OOP_EPS;
  EXPECT_EQ(first.EqMatrix(second), false);
}

TEST(SumMatrix, Subtest_1) {
  S21Matrix first(2, 3), second(2, 3), third(2, 3);

  first(0, 0) = 324;
  second(0, 0) = 234;
  third(0, 0) = 324 + 234;

  first(0, 1) = 2;
  second(0, 1) = 4;
  third(0, 1) = 6;

  first(0, 2) = 1;
  second(0, 2) = -1;
  third(0, 2) = 0;

  first(1, 0) = 1;
  second(1, 0) = 15;
  third(1, 0) = 16;

  first(1, 1) = -2;
  second(1, 1) = 4;
  third(1, 1) = 2;

  first(1, 2) = -1;
  second(1, 2) = -1;
  third(1, 2) = -2;

  first.SumMatrix(second);

  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(SumMatrix, Subtest_2) {
  S21Matrix first(3, 2), second(3, 2), third(3, 2);

  first(0, 0) = 324;
  second(0, 0) = 234;
  third(0, 0) = 324 + 234;

  first(0, 1) = 2;
  second(0, 1) = 4;
  third(0, 1) = 6;

  first(1, 0) = 1;
  second(1, 0) = 15;
  third(1, 0) = 16;

  first(1, 1) = -2;
  second(1, 1) = 4;
  third(1, 1) = 2;

  first(2, 0) = 1;
  second(2, 0) = -1;
  third(2, 0) = 0;

  first(2, 1) = -1;
  second(2, 1) = -1;
  third(2, 1) = -2;

  first.SumMatrix(second);

  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(SumMatrix, Subtest_3) {
  S21Matrix first(2, 3), second(3, 3);
  EXPECT_ANY_THROW(first.SumMatrix(second));

  S21Matrix third(2, 3), forth(2, 4);
  EXPECT_ANY_THROW(third.SumMatrix(forth));

  S21Matrix fifth(2, 3), sixth(4, 4);
  EXPECT_ANY_THROW(fifth.SumMatrix(sixth));
}

TEST(SubMatrix, Subtest_1) {
  S21Matrix first(2, 3), second(2, 3), third(2, 3);

  first(0, 0) = 324;
  second(0, 0) = 234;
  third(0, 0) = 324 + 234;

  first(0, 1) = 2;
  second(0, 1) = 4;
  third(0, 1) = 6;

  first(0, 2) = 1;
  second(0, 2) = -1;
  third(0, 2) = 0;

  first(1, 0) = 1;
  second(1, 0) = 15;
  third(1, 0) = 16;

  first(1, 1) = -2;
  second(1, 1) = 4;
  third(1, 1) = 2;

  first(1, 2) = -1;
  second(1, 2) = -1;
  third(1, 2) = -2;

  third.SubMatrix(second);

  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(SubMatrix, Subtest_2) {
  S21Matrix first(3, 2), second(3, 2), third(3, 2);

  first(0, 0) = 324;
  second(0, 0) = 234;
  third(0, 0) = 324 + 234;

  first(0, 1) = 2;
  second(0, 1) = 4;
  third(0, 1) = 6;

  first(1, 0) = 1;
  second(1, 0) = 15;
  third(1, 0) = 16;

  first(1, 1) = -2;
  second(1, 1) = 4;
  third(1, 1) = 2;

  first(2, 0) = 1;
  second(2, 0) = -1;
  third(2, 0) = 0;

  first(2, 1) = -1;
  second(2, 1) = -1;
  third(2, 1) = -2;

  third.SubMatrix(second);

  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(SubMatrix, Subtest_3) {
  S21Matrix first(2, 3), second(3, 3);
  EXPECT_ANY_THROW(first.SubMatrix(second));

  S21Matrix third(2, 3), forth(2, 4);
  EXPECT_ANY_THROW(third.SubMatrix(forth));

  S21Matrix fifth(2, 3), sixth(4, 4);
  EXPECT_ANY_THROW(fifth.SubMatrix(sixth));
}

TEST(MulNumber, Subtest_1) {
  S21Matrix first(2, 4), second(2, 4);
  const double n = 1.2;

  first(0, 0) = 2;
  second(0, 0) = 2 * n;

  first(0, 1) = 3;
  second(0, 1) = 3 * n;

  first(0, 2) = 1;
  second(0, 2) = 1 * n;

  first(0, 3) = -0.2;
  second(0, 3) = -0.2 * n;

  first(1, 0) = 54;
  second(1, 0) = 54 * n;

  first(1, 1) = -87;
  second(1, 1) = -87 * n;

  first(1, 2) = 61;
  second(1, 2) = 61 * n;

  first(1, 3) = 34;
  second(1, 3) = 34 * n;

  first.MulNumber(n);
  EXPECT_EQ(first.EqMatrix(second), true);
}

TEST(MulMatrix, Subtest_1) {
  S21Matrix first(2, 4), second(4, 3), third(2, 3);

  first(0, 0) = 3;
  first(0, 1) = 2;
  first(0, 2) = -1;
  first(0, 3) = -5;
  first(1, 0) = 2;
  first(1, 1) = -7;
  first(1, 2) = -2;
  first(1, 3) = 6;

  second(0, 0) = 1;
  second(0, 1) = 2;
  second(0, 2) = 3;
  second(1, 0) = -3;
  second(1, 1) = 4;
  second(1, 2) = -5;
  second(2, 0) = -2;
  second(2, 1) = 7.4;
  second(2, 2) = -6;
  second(3, 0) = 2.3;
  second(3, 1) = -2;
  second(3, 2) = 1.2;

  third(0, 0) = -12.5;
  third(0, 1) = 16.6;
  third(0, 2) = -1;
  third(1, 0) = 40.8;
  third(1, 1) = -50.8;
  third(1, 2) = 60.2;

  first.MulMatrix(second);

  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(MulMatrix, Subtest_2) {
  S21Matrix first(2, 3), second(2, 3);
  EXPECT_ANY_THROW(first.MulMatrix(second));
}

TEST(MulMatrix, Subtest_3) {
  S21Matrix first(2, 2), second(3, 3);
  EXPECT_ANY_THROW(first.MulMatrix(second));
}

TEST(Transpose, Subtest_1) {
  S21Matrix first(2, 3), second(3, 2);

  first(0, 0) = 324;
  second(0, 0) = 324;
  first(0, 1) = 2;
  second(1, 0) = 2;
  first(0, 2) = 1;
  second(2, 0) = 1;
  first(1, 0) = 1;
  second(0, 1) = 1;
  first(1, 1) = -2;
  second(1, 1) = -2;
  first(1, 2) = -1;
  second(2, 1) = -1;

  S21Matrix third = first.Transpose();
  EXPECT_EQ(third.EqMatrix(second), true);
  EXPECT_EQ(first.EqMatrix(third.Transpose()), true);
}

TEST(CalcComplement, Subtest_1) {
  S21Matrix first, second;

  first(0, 0) = 3;
  first(0, 1) = 2;
  first(0, 2) = 1;
  first(1, 0) = 4;
  first(1, 1) = -2;
  first(1, 2) = -1;
  first(2, 0) = 2;
  first(2, 1) = -5;
  first(2, 2) = 7;

  second(0, 0) = -19;
  second(0, 1) = -30;
  second(0, 2) = -16;
  second(1, 0) = -19;
  second(1, 1) = 19;
  second(1, 2) = 19;
  second(2, 0) = 0;
  second(2, 1) = 7;
  second(2, 2) = -14;

  S21Matrix third = first.CalcComplements();
  EXPECT_EQ(third.EqMatrix(second), true);
}

TEST(CalcComplement, Subtest_2) {
  S21Matrix first(2, 2), second(2, 2);

  first(0, 0) = 3;
  first(0, 1) = 2;
  first(1, 0) = 4;
  first(1, 1) = -2;

  second(0, 0) = -2;
  second(0, 1) = -4;
  second(1, 0) = -2;
  second(1, 1) = 3;

  S21Matrix third = first.CalcComplements();
  EXPECT_EQ(third.EqMatrix(second), true);
}

TEST(CalcComplement, Subtest_3) {
  S21Matrix first(1, 1), second(1, 1);
  first(0, 0) = 3;
  second(0, 0) = 1;

  S21Matrix third = first.CalcComplements();
  EXPECT_EQ(third.EqMatrix(second), true);
}

TEST(CalcComplement, Subtest_4) {
  S21Matrix first(5, 5), second(5, 5);

  first(0, 0) = 3;
  first(0, 2) = 12;
  first(1, 3) = 4;
  first(2, 0) = 1;
  first(3, 1) = 2;
  first(4, 2) = 2;
  first(4, 4) = 5;

  second(0, 2) = 40;
  second(0, 4) = -16;
  second(1, 3) = 120;
  second(2, 0) = 480;
  second(2, 2) = -120;
  second(2, 4) = 48;
  second(3, 1) = 240;
  second(4, 4) = 96;

  S21Matrix third = first.CalcComplements();

  EXPECT_EQ(third.EqMatrix(second), true);
}

TEST(CalcComplement, Subtest_5) {
  S21Matrix first(3, 5), second(3, 2);

  EXPECT_ANY_THROW(first.CalcComplements());
  EXPECT_ANY_THROW(second.CalcComplements());
}

TEST(Determinant, Subtest_1) {
  S21Matrix first(5, 5);

  first(0, 0) = 3;
  first(0, 1) = 12;
  first(0, 2) = 4;
  first(0, 3) = 1;
  first(0, 4) = 2;

  first(1, 0) = -1;
  first(1, 1) = 2;
  first(1, 2) = 5;
  first(1, 3) = 3;
  first(1, 4) = -2;

  first(2, 0) = 2;
  first(2, 1) = 2;
  first(2, 2) = 1;
  first(2, 3) = 3;
  first(2, 4) = 4;

  first(3, 0) = -1;
  first(3, 1) = 2;
  first(3, 2) = 3;
  first(3, 3) = 7;
  first(3, 4) = -5;

  first(4, 0) = 6;
  first(4, 1) = 4;
  first(4, 2) = 2;
  first(4, 3) = 2;
  first(4, 4) = 3;

  double expected = -6748;

  EXPECT_EQ(first.Determinant(), expected);
}

TEST(Determinant, Subtest_2) {
  S21Matrix first;

  first(0, 0) = 3;
  first(0, 1) = -5;
  first(0, 2) = 7;
  first(1, 0) = -1;
  first(1, 1) = -3;
  first(1, 2) = 7;
  first(2, 0) = -2;
  first(2, 1) = 12;
  first(2, 2) = 1;

  double expected = -322;

  EXPECT_EQ(first.Determinant(), expected);
}

TEST(Determinant, Subtest_3) {
  S21Matrix first(1, 1);

  first(0, 0) = 3;

  double expected = 3;

  EXPECT_EQ(first.Determinant(), expected);
}

TEST(Determinant, Subtest_4) {
  S21Matrix first(3, 5), second(3, 2);

  EXPECT_ANY_THROW(first.Determinant());
  EXPECT_ANY_THROW(second.Determinant());
}

TEST(InverseMatrix, Subtest_1) {
  S21Matrix first(5, 5), second(5, 5);

  first(0, 1) = 3;
  first(0, 2) = 1;
  first(0, 4) = 1;
  first(1, 0) = 1;
  first(1, 3) = 2;
  first(2, 1) = 1;
  first(2, 2) = 2;
  first(3, 0) = 2;
  first(3, 3) = 1;
  first(4, 1) = 1;
  first(4, 4) = 2;

  second(0, 1) = -1. / 3;
  second(0, 3) = 2. / 3;
  second(1, 0) = 1. / 2;
  second(1, 2) = -1. / 4;
  second(1, 4) = -1. / 4;
  second(2, 0) = -1. / 4;
  second(2, 2) = 5. / 8;
  second(2, 4) = 1. / 8;
  second(3, 1) = 2. / 3;
  second(3, 3) = -1. / 3;
  second(4, 0) = -1. / 4;
  second(4, 2) = 1. / 8;
  second(4, 4) = 5. / 8;

  S21Matrix third = first.InverseMatrix();

  EXPECT_EQ(third.EqMatrix(second), true);
}

TEST(InverseMatrix, Subtest_2) {
  S21Matrix first, second;

  first(0, 0) = 1;
  first(0, 1) = 4;
  first(0, 2) = 4;
  first(1, 0) = 1;
  first(1, 1) = 2;
  first(1, 2) = 2;
  first(2, 0) = 4;
  first(2, 1) = 1;
  first(2, 2) = 2;

  second(0, 0) = -1;
  second(0, 1) = 2;
  second(0, 2) = 0;
  second(1, 0) = -3;
  second(1, 1) = 7;
  second(1, 2) = -1;
  second(2, 0) = 3.5;
  second(2, 1) = -7.5;
  second(2, 2) = 1;

  S21Matrix third = first.InverseMatrix();

  EXPECT_EQ(third.EqMatrix(second), true);
}

TEST(InverseMatrix, Subtest_3) {
  S21Matrix first(3, 5), second(3, 2);

  EXPECT_ANY_THROW(first.InverseMatrix());
  EXPECT_ANY_THROW(second.InverseMatrix());
}

TEST(InverseMatrix, Subtest_4) {
  S21Matrix first;
  first(0, 0) = 1;
  first(0, 1) = 1;
  first(0, 2) = 1;
  first(1, 0) = 2;
  first(1, 1) = 2;
  first(1, 2) = 2;
  first(2, 0) = 3;
  first(2, 1) = 3;
  first(2, 2) = 3;
  EXPECT_ANY_THROW(first.InverseMatrix());
}

TEST(OperatorsSum, Subtest_1) {
  S21Matrix first(2, 3), second(2, 3), third(2, 3);

  first(0, 1) = 2;
  second(0, 1) = -4;
  third(0, 1) = -2;

  first(0, 2) = 21;
  second(0, 2) = -1;
  third(0, 2) = 20;

  first(1, 2) = -21;
  second(1, 2) = 10;
  third(1, 2) = -11;

  EXPECT_EQ(third.EqMatrix(first + second), true);

  first += second;
  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(OperatorsSub, Subtest_1) {
  S21Matrix first(2, 3), second(2, 3), third(2, 3);

  first(0, 1) = 32;
  second(0, 1) = 15;
  third(0, 1) = 17;

  first(0, 2) = 3;
  second(0, 2) = -1;
  third(0, 2) = 4;

  first(1, 2) = 2;
  second(1, 2) = -9;
  third(1, 2) = 11;

  EXPECT_EQ(third.EqMatrix(first - second), true);

  first -= second;
  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(OperatorsMulMatrix, Subtest_1) {
  S21Matrix first(3, 2), second(2, 4), third(3, 4);

  first(0, 0) = 3;
  first(0, 1) = 2;
  first(1, 0) = 2;
  first(1, 1) = -7;
  first(2, 0) = 0;
  first(2, 1) = 1;

  second(0, 0) = 1;
  second(0, 1) = 2;
  second(0, 2) = 3;
  second(0, 3) = 0;
  second(1, 0) = -3;
  second(1, 1) = 4;
  second(1, 2) = -5;
  second(1, 3) = 1;

  third(0, 0) = -3;
  third(0, 1) = 14;
  third(0, 2) = -1;
  third(0, 3) = 2;
  third(1, 0) = 23;
  third(1, 1) = -24;
  third(1, 2) = 41;
  third(1, 3) = -7;
  third(2, 0) = -3;
  third(2, 1) = 4;
  third(2, 2) = -5;
  third(2, 3) = 1;

  EXPECT_EQ(third.EqMatrix(first * second), true);

  first *= second;
  EXPECT_EQ(third.EqMatrix(first), true);
}

TEST(OperatorsMulNumber, Subtest_1) {
  S21Matrix first(3, 2), second(3, 2);

  first(0, 0) = 3;
  first(0, 1) = 2;
  first(1, 0) = 2;
  first(1, 1) = -7;
  first(2, 0) = 0;
  first(2, 1) = 1;

  second(0, 0) = 9;
  second(0, 1) = 6;
  second(1, 0) = 6;
  second(1, 1) = -21;
  second(2, 0) = 0;
  second(2, 1) = 3;

  EXPECT_EQ(second.EqMatrix(first * 3), true);

  first *= 3;
  EXPECT_EQ(second.EqMatrix(first), true);
}

TEST(OperatorEq, Subtest_1) {
  S21Matrix first(2, 5), second(2, 5);
  EXPECT_EQ(first == second, true);

  first(0, 0) = 1;
  second(0, 0) = 1;
  first(1, 2) = -4;
  second(1, 2) = -4;
  first(1, 4) = 4;
  second(1, 4) = 4;
  EXPECT_EQ(first == second, true);

  first(1, 3) = 5;
  second(1, 3) = 5 + 0.99 * S21_MATRIX_OOP_EPS;
  EXPECT_EQ(first == second, true);

  first(1, 3) = 5;
  second(1, 3) = 5 + 2 * S21_MATRIX_OOP_EPS;
  EXPECT_EQ(first == second, false);
}

TEST(OperatorIndex, Subtest_1) {
  S21Matrix first(2, 5);
  first(0, 0) = 1;
  first(0, 3) = -2;
  first(1, 4) = 3;
  const S21Matrix second = first;

  EXPECT_EQ(second(0, 0), 1);
  EXPECT_EQ(second(0, 3), -2);
  EXPECT_EQ(second(1, 4), 3);
  EXPECT_EQ(second(0, 1), 0);
}

TEST(OperatorIndex, Subtest_2) {
  S21Matrix first(4, 3);
  first(0, 0) = 1;
  first(0, 2) = -2;
  first(1, 2) = 3;
  EXPECT_EQ(first(0, 0), 1);
  EXPECT_ANY_THROW(first(4, 3));
  EXPECT_ANY_THROW(first(1, 3));
  EXPECT_ANY_THROW(first(4, 2));
  EXPECT_ANY_THROW(first(-1, 1));
  EXPECT_ANY_THROW(first(1, -1));

  const S21Matrix second = first;
  EXPECT_EQ(second(0, 0), 1);
  EXPECT_ANY_THROW(second(4, 3));
  EXPECT_ANY_THROW(second(1, 3));
  EXPECT_ANY_THROW(second(4, 2));
  EXPECT_ANY_THROW(second(-1, 1));
  EXPECT_ANY_THROW(second(1, -1));
}

TEST(CopyAssignment, Subtest_1) {
  S21Matrix first(4, 5);
  first(0, 0) = 1;
  first(0, 3) = 2;
  first(1, 4) = 3;
  first(3, 4) = 4;

  S21Matrix second;
  second = first;
  EXPECT_EQ(first.EqMatrix(second), true);
  EXPECT_EQ(first(0, 0), 1);
  EXPECT_EQ(first(3, 4), 4);

  const S21Matrix third = first * 2;
  second = third;
  EXPECT_EQ(second.EqMatrix(third), true);
  EXPECT_EQ(second(0, 0), 2);
  EXPECT_EQ(second(3, 4), 8);
}

TEST(MoveAssignment, Subtest_1) {
  S21Matrix first(4, 5);
  first(0, 0) = 1;
  first(0, 3) = 2;
  first(1, 4) = 3;
  first(3, 4) = 4;
  S21Matrix copy_first = first;

  S21Matrix second;
  second = std::move(first);
  EXPECT_EQ(second.EqMatrix(copy_first), true);
  EXPECT_EQ(second(0, 0), 1);
  EXPECT_ANY_THROW(first(0, 0));
}

TEST(GettersAndSetters, Subtest_1) {
  S21Matrix first;
  EXPECT_EQ(first.GetRows(), 3);
  EXPECT_EQ(first.GetCols(), 3);

  first.SetRows(1);
  first.SetCols(2);
  EXPECT_EQ(first.GetRows(), 1);
  EXPECT_EQ(first.GetCols(), 2);

  first.SetRows(4);
  first.SetCols(5);
  EXPECT_EQ(first.GetRows(), 4);
  EXPECT_EQ(first.GetCols(), 5);
  S21Matrix second(4, 5);
  EXPECT_EQ(second.EqMatrix(first), true);
}

TEST(GettersAndSetters, Subtest_2) {
  const S21Matrix first(2, 4);
  EXPECT_EQ(first.GetRows(), 2);
  EXPECT_EQ(first.GetCols(), 4);
}

TEST(GettersAndSetters, Subtest_3) {
  S21Matrix first(2, 4);
  EXPECT_ANY_THROW(first.SetRows(-1));
  EXPECT_ANY_THROW(first.SetCols(-2));
  EXPECT_ANY_THROW(first.SetRows(0));
  EXPECT_ANY_THROW(first.SetCols(0));
  EXPECT_EQ(first.GetRows(), 2);
  EXPECT_EQ(first.GetCols(), 4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}