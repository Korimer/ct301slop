#pragma once

#include <string>


enum class TokenType {
  Number,
  Operator,
  LParen,
  RParen,
  Invalid
};

struct Token {
  TokenType type;
  std::string text;

  Token(const std::string&);

  const char* toString(TokenType type);
};
