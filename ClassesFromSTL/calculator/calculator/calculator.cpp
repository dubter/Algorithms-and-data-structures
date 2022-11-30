#include "calculator.h"

int CalculateExpression(std::string_view input) {
  std::vector<Token> tokens = Tokenize(input);

  for (size_t i = 0; i < tokens.size(); ++i) {
    if (std::holds_alternative<UnknownToken>(tokens[i])) {
      throw UnknownSymbolError();
    }
  }

  size_t begin = 0;
  auto root = ParseExpression(tokens, begin);
  if (begin != tokens.size()) {
    throw WrongExpressionError();
  }
  return root->Calculate();
}