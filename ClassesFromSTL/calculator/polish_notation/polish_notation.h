#pragma once
#include <string>
#include <stdexcept>
#include "expression.h"
#include <memory>

#include "../tokenize/tokenize.h"

class UnknownSymbolError : public std::runtime_error {
 public:
  explicit UnknownSymbolError(const std::string& symbol = "") : std::runtime_error("UnknownSymbolError: " + symbol) {
  }
};

class WrongExpressionError : public std::runtime_error {
 public:
  explicit WrongExpressionError(const std::string& msg = "") : std::runtime_error("WrongExpressionError: " + msg) {
  }
};

int CalculatePolishNotation(std::string_view input);

std::unique_ptr<IExpression> BuildTree(const std::vector<Token>&, size_t&);