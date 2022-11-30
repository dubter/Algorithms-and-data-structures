#pragma once
#include <memory>
#include "../tokenize/tokenize.h"

class IExpression {
 public:
  virtual int Calculate() const = 0;
  virtual ~IExpression() = default;
};

class Constant : public IExpression {
 public:
  Constant(int val) : val_(val) {  // NOLINT
  }

  int Calculate() const override {
    return val_;
  }

 private:
  int val_;
};

class IUnaryOperation : public IExpression {
 public:
  IUnaryOperation(std::unique_ptr<IExpression> &&other) : operand_(std::move(other)) {  // NOLINT
  }

  virtual int Operation(int) const = 0;

  int Calculate() const override {
    return Operation(operand_->Calculate());
  }

 private:
  std::unique_ptr<IExpression> operand_;
};

class IBinaryOperation : public IExpression {
 public:
  IBinaryOperation(std::unique_ptr<IExpression> &&first, std::unique_ptr<IExpression> &&second) {  // NOLINT
    first_ = std::move(first);
    second_ = std::move(second);
  }

  virtual int Operation(int, int) const = 0;

  int Calculate() const override {
    return Operation(first_->Calculate(), second_->Calculate());
  }

 private:
  std::unique_ptr<IExpression> first_;
  std::unique_ptr<IExpression> second_;
};

class Sum : public IBinaryOperation {
 public:
  Sum(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return lhs + rhs;
  }
};

class Subtract : public IBinaryOperation {
 public:
  Subtract(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return lhs - rhs;
  }
};

class Multiply : public IBinaryOperation {
 public:
  Multiply(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return lhs * rhs;
  }
};

class Divide : public IBinaryOperation {  // возможно деление на 0
 public:
  Divide(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return lhs / rhs;
  }
};

class Residual : public IBinaryOperation {
 public:
  Residual(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return lhs % rhs;
  }
};

class Minimum : public IBinaryOperation {
 public:
  Minimum(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return std::min(lhs, rhs);
  }
};

class Maximum : public IBinaryOperation {
 public:
  Maximum(std::unique_ptr<IExpression> &&operand1, std::unique_ptr<IExpression> &&operand2)
      : IBinaryOperation(std::move(operand1), std::move(operand2)) {
  }
  int Operation(int lhs, int rhs) const override {
    return std::max(lhs, rhs);
  }
};

class AbsoluteValue : public IUnaryOperation {
 public:
  AbsoluteValue(std::unique_ptr<IExpression> &&operand1) : IUnaryOperation(std::move(operand1)) {  // NOLINT
  }
  int Operation(int value) const override {
    return std::abs(value);
  }
};

class Square : public IUnaryOperation {
 public:
  Square(std::unique_ptr<IExpression> &&operand1) : IUnaryOperation(std::move(operand1)) {  // NOLINT
  }
  int Operation(int value) const override {
    return (value * value);
  }
};