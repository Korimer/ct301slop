
#include "parser.h"
#include "operation.h"
#include "element.h"
#include "token.h"
#include "exceptions.h"

#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void Parser::reset() {
  this->elements = std::stack<std::unique_ptr<Element>>();
  this->operators = std::stack<std::unique_ptr<Operator>>();
}

void Parser::reduce() {
  unique_ptr<Operator> op = operators.top().get();
  operators.pop();
  unique_ptr<Element> lhs = elements.top().get();
  elements.pop();
  unique_ptr<Element> rhs = elements.top().get();
  elements.pop();

  Operation operation = Operation(lhs,op,rhs); 
  elements.push()
}

Element* Parser::Parse(const string& equationStr) {
  this->reset();

  std::vector<Token> tokens = std::vector<Token>();

  std::istringstream in(equationStr);
  std::string token;

  while (in >> token) {
    tokens.push_back(Token(token));
  }

  try {
    for (const Token& token : tokens) {
      next(token);
    }
  } catch (InvalidEquationStructure) {
    return nullptr;
  }

  if (!operators.empty()) {
    return nullptr;
  }
  if (elements.empty()) {
    return nullptr;
  }
  auto fullEq = elements.top();
  elements.pop();
  if (!elements.empty()) {
    return nullptr;
  }

  return fullEq;
}


void Parser::next(const Token& token) {
  switch (token.type) {
    case TokenType::Operator: op();
    case TokenType::Number:   num();
    case TokenType::LParen:   opnParen();
    case TokenType::RParen:   closeParen();
    case TokenType::Invalid:  throw InvalidEquationStructure("Error: Invalid token.");
  }
}

void Parser::op() {

}
void Parser::num() {

}
void Parser::opnParen() {

}
void Parser::closeParen() {

}
