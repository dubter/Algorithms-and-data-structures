#include "polish_notation.h"

std::unique_ptr<IExpression> BuildTree(const std::vector<Token> &tokens, size_t &idx) {

  if (idx >= tokens.size()) {
    throw WrongExpressionError();
  }

  if (std::holds_alternative<UnknownToken>(tokens[idx])) {
    throw UnknownSymbolError();
  }

  if (std::holds_alternative<NumberToken>(tokens[idx])) {
    auto tree = std::unique_ptr<IExpression>(new Constant{std::get<NumberToken>(tokens[idx]).value});
    ++idx;
    return tree;
  }

  if (std::holds_alternative<PlusToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Sum(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<MinusToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Subtract(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<MultiplyToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Multiply(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<DivideToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Divide(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<ResidualToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Residual(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<MinToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Minimum(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<MaxToken>(tokens[idx])) {
    auto first_tree = BuildTree(tokens, ++idx);
    auto second_tree = BuildTree(tokens, idx);
    auto res_tree = std::unique_ptr<IExpression>(new Maximum(std::move(first_tree), std::move(second_tree)));
    return res_tree;
  }

  if (std::holds_alternative<AbsToken>(tokens[idx])) {
    ++idx;
    auto tree = BuildTree(tokens, idx);
    auto res = std::unique_ptr<IExpression>(new AbsoluteValue(std::move(tree)));
    return res;
  }

  if (std::holds_alternative<SqrToken>(tokens[idx])) {
    ++idx;
    auto tree = BuildTree(tokens, idx);
    auto res = std::unique_ptr<IExpression>(new Square(std::move(tree)));
    return res;
  }
  return nullptr;
}

int CalculatePolishNotation(std::string_view input) {
  std::vector<Token> tokens = Tokenize(input);
  size_t begin = 0;
  auto root = BuildTree(tokens, begin);
  if (begin != tokens.size()) {
    throw WrongExpressionError();
  }
  return root->Calculate();
}