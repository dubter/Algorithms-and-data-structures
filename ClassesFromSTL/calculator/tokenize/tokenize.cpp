#include "tokenize.h"

bool PlusToken::operator==(const PlusToken &) const {
  return true;
}

bool MinusToken::operator==(const MinusToken &) const {
  return true;
}

bool MultiplyToken::operator==(const MultiplyToken &) const {
  return true;
}

bool DivideToken::operator==(const DivideToken &) const {
  return true;
}

bool ResidualToken::operator==(const ResidualToken &) const {
  return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken &) const {
  return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken &) const {
  return true;
}

bool SqrToken::operator==(const SqrToken &) const {
  return true;
}

bool MaxToken::operator==(const MaxToken &) const {
  return true;
}

bool MinToken::operator==(const MinToken &) const {
  return true;
}

bool AbsToken::operator==(const AbsToken &) const {
  return true;
}

bool NumberToken::operator==(const NumberToken &other) const {
  return value == other.value;
}

bool UnknownToken::operator==(const UnknownToken &other) const {
  return value == other.value;
}

std::vector<Token> Tokenize(std::string_view str) {
  std::vector<Token> tokens;

  size_t len = str.size();
  size_t chars_len = 0;
  size_t nums_len = 0;

  std::string token;

  for (size_t i = 0; i < len; ++i) {

    if (str[i] != ' ') {
      token.push_back(str[i]);

      if (static_cast<int>(str[i]) >= static_cast<int>('0') && static_cast<int>(str[i]) <= static_cast<int>('9')) {
        ++nums_len;
      }

      if (static_cast<int>(str[i]) < static_cast<int>('0') || static_cast<int>(str[i]) > static_cast<int>('9')) {
        ++chars_len;
      }
    }

    if ((str[i] == ' ' || i == len - 1) && nums_len + chars_len > 0) {
      if (token == "+") {
        tokens.emplace_back(PlusToken{});
      } else if (token == "-") {
        tokens.emplace_back(MinusToken{});
      } else if (token == "*") {
        tokens.emplace_back(MultiplyToken{});
      } else if (token == "/") {
        tokens.emplace_back(DivideToken{});
      } else if (token == "%") {
        tokens.emplace_back(ResidualToken{});
      } else if (token == "(") {
        tokens.emplace_back(OpeningBracketToken{});
      } else if (token == ")") {
        tokens.emplace_back(ClosingBracketToken{});
      } else if (token == "sqr") {
        tokens.emplace_back(SqrToken{});
      } else if (token == "max") {
        tokens.emplace_back(MaxToken{});
      } else if (token == "min") {
        tokens.emplace_back(MinToken{});
      } else if (token == "abs") {
        tokens.emplace_back(AbsToken{});
      } else if (nums_len && !chars_len) {
        tokens.emplace_back(NumberToken{(std::stoi(token))});
      } else if (chars_len == 1 && token[0] == '+' && nums_len > 0) {
        tokens.emplace_back(NumberToken{(std::stoi(token))});
      } else if (chars_len == 1 && token[0] == '-' && nums_len > 0) {
        tokens.emplace_back(NumberToken{(std::stoi(token))});
      } else {
        tokens.emplace_back(UnknownToken{token});
      }
      token = "";
      chars_len = 0;
      nums_len = 0;
    }
  }
  return tokens;
}