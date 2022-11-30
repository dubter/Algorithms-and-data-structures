#include "parser.h"

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& tokens, size_t& pos) {

  auto first = ParseAddendum(tokens, pos);
  while (pos < tokens.size() &&
      (std::holds_alternative<PlusToken>(tokens[pos]) || std::holds_alternative<MinusToken>(tokens[pos]))) {

    if (std::holds_alternative<PlusToken>(tokens[pos])) {

      auto second = ParseAddendum(tokens, ++pos);
      first = std::unique_ptr<IExpression>(new Sum(std::move(first), std::move(second)));
    } else if (std::holds_alternative<MinusToken>(tokens[pos])) {
      auto second = ParseAddendum(tokens, ++pos);
      first = std::unique_ptr<IExpression>(new Subtract(std::move(first), std::move(second)));
    }
  }
  return first;
}

std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& tokens, size_t& pos) {
  auto first = ParseMultiplier(tokens, pos);
  while (pos < tokens.size() &&
      (std::holds_alternative<MultiplyToken>(tokens[pos]) || std::holds_alternative<DivideToken>(tokens[pos]) ||
          std::holds_alternative<ResidualToken>(tokens[pos]))) {

    if (std::holds_alternative<MultiplyToken>(tokens[pos])) {

      auto second = ParseMultiplier(tokens, ++pos);
      first = std::unique_ptr<IExpression>(new Multiply(std::move(first), std::move(second)));
    } else if (std::holds_alternative<DivideToken>(tokens[pos])) {
      auto second = ParseMultiplier(tokens, ++pos);
      first = std::unique_ptr<IExpression>(new Divide(std::move(first), std::move(second)));
    } else if (std::holds_alternative<ResidualToken>(tokens[pos])) {
      auto second = ParseMultiplier(tokens, ++pos);
      first = std::unique_ptr<IExpression>(new Residual(std::move(first), std::move(second)));
    }
  }

  return first;
}

std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError();
  }
  if (std::holds_alternative<NumberToken>(tokens[pos])) {
    return std::unique_ptr<IExpression>(new Constant(std::get<NumberToken>(tokens[pos++]).value));
  }

  if (std::holds_alternative<OpeningBracketToken>(tokens[pos])) {
    auto parse_exp = ParseExpression(tokens, ++pos);
    if (!std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      throw WrongExpressionError();
    }
    ++pos;

    return parse_exp;
  }
  throw WrongExpressionError();
}