#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) { CreateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CheckRowsAndColsArePositive();
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.ResetData();
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

void S21Matrix::CheckRowsAndColsArePositive() const {
  if (cols_ <= 0 || rows_ <= 0)
    throw std::logic_error(
        "Numbers of rows and columns in a matrix must be positive");
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::DeleteMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void S21Matrix::ResetData() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix copy = other;
  Swap(copy);
  return *this;
}

void S21Matrix::Swap(S21Matrix& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    DeleteMatrix();

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.ResetData();
  }
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (other.cols_ != cols_ || other.rows_ != rows_) return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > S21_MATRIX_OOP_EPS)
        return false;
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  CheckMatricesHaveSameDimensions(other);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  CheckMatricesHaveSameDimensions(other);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::logic_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  CheckMatrixIsSquare();
  int size = rows_;
  S21Matrix result(size, size);
  if (size == 1) {
    result.matrix_[0][0] = 1;
  } else {
    S21Matrix minor(size - 1, size - 1);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        FillMinor(i, j, minor);
        int sign = ((i + j) % 2 ? -1 : 1);
        result.matrix_[i][j] = minor.Determinant() * sign;
      }
    }
  }
  return result;
}

void S21Matrix::FillMinor(int row, int col, S21Matrix& minor) const {
  CheckMatrixIndexesAreInRange(row, col);

  int past_row = 0;
  for (int i = 0; i < rows_ - 1; i++) {
    int past_col = 0;
    if (i == row) {
      past_row = 1;
    }
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == col) {
        past_col = 1;
      }
      minor.matrix_[i][j] = matrix_[i + past_row][j + past_col];
    }
  }
}

void S21Matrix::CheckMatrixIndexesAreInRange(int row, int col) const {
  if (row >= rows_ || row < 0 || col >= cols_ || col < 0)
    throw std::out_of_range("Index is outside the matrix");
}

double S21Matrix::Determinant() const {
  CheckMatrixIsSquare();
  int size = rows_;
  double result = 0;
  if (size == 1) {
    result = matrix_[0][0];
  } else {
    S21Matrix minor(size - 1, size - 1);
    for (int j = 0; j < cols_; j++) {
      FillMinor(0, j, minor);
      int sign = (j % 2 ? -1 : 1);
      result += matrix_[0][j] * minor.Determinant() * sign;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (det == 0) throw std::logic_error("The matrix is not invertible");
  S21Matrix result = CalcComplements();
  result = result.Transpose();
  result.MulNumber(1 / det);
  return result;
}

void S21Matrix::CheckMatrixIsSquare() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square");
  }
}

void S21Matrix::CheckMatricesHaveSameDimensions(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Matrices must have the same dimensions");
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) {
  CheckMatrixIndexesAreInRange(row, col);
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  CheckMatrixIndexesAreInRange(row, col);
  return matrix_[row][col];
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw std::logic_error("The number of rows must be positive");

  if (rows < rows_) {
    for (int i = rows_ - 1; i >= rows; i--) {
      delete[] matrix_[i];
    }
    rows_ = rows;
  } else if (rows > rows_) {
    S21Matrix temp(rows, cols_);
    temp.CopyMatrixValues(*this);
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw std::logic_error("The number of rows must be positive");

  S21Matrix temp(rows_, cols);
  temp.CopyMatrixValues(*this);
  *this = std::move(temp);
}

void S21Matrix::CopyMatrixValues(const S21Matrix& other) {
  int min_rows = std::min(rows_, other.rows_);
  int min_cols = std::min(cols_, other.cols_);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < min_cols; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}