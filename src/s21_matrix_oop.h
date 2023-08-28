#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

#define S21_MATRIX_OOP_EPS 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  void CheckRowsAndColsArePositive() const;
  void CheckMatrixIndexesAreInRange(int row, int col) const;
  void CheckMatrixIsSquare() const;
  void CheckMatricesHaveSameDimensions(const S21Matrix& other) const;
  void CreateMatrix();
  void ResetData();
  void DeleteMatrix();
  void FillMinor(int row, int col, S21Matrix& minor) const;
  void CopyMatrixValues(const S21Matrix& other);
  void Swap(S21Matrix& other);
};

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_