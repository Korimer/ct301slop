#include "token.h"
#include "element.h"
#include "operator.h"

using namespace std;

// Claude boilerplate
TokenType classify(const string& tok) {
  if (tok == "(") { return TokenType::LParen; }
  if (tok == ")") { return TokenType::RParen; } if (Operator::is_operator(tok)) { return TokenType::Operator; }
  if (Element::canConvertToElement(tok)) { return TokenType::Number; }
  return TokenType::Invalid;
}


const char* toString(TokenType type) {
  switch (type) {
    case TokenType::Number:   return "Number";
    case TokenType::Operator: return "Operator";
    case TokenType::LParen:   return "LParen";
    case TokenType::RParen:   return "RParen";
    case TokenType::Invalid:  return "Invalid";
  }
  return "Invalid";
}


Token::Token(const string& text):
  type(classify(text)), text(text) { }
