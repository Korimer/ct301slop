#include "parser.h"
#include "element.h"
#include "exceptions.h"
#include "operation.h"
#include "operator.h"
#include "token.h"

#include <sstream>

using namespace std;

int Parser::precedence(char c) {
  switch (c) {
    case '*': case '/': case '%': return 2;
    case '+': case '-':           return 1;
    default:                      return 0;
  }
}

void Parser::reset() {
  elements = stack<unique_ptr<Element>>();
  operators = stack<char>();
  expectOperand = true;
}

void Parser::reduce() {
  if (operators.empty() || operators.top() == '(' || elements.size() < 2) {
    throw InvalidEquationStructure("Missing operand or operator");
  }

  Operator op(operators.top());
  operators.pop();

  unique_ptr<Element> rhs = std::move(elements.top());
  elements.pop();
  unique_ptr<Element> lhs = std::move(elements.top());
  elements.pop();

  elements.push(make_unique<Operation>(*lhs, op, *rhs));
}

Element* Parser::Parse(const string& equationStr) {
  reset();

  istringstream in(equationStr);
  string word;
  while (in >> word) {
    next(Token(word));
  }

  if (expectOperand) {
    throw InvalidEquationStructure("Expression ended where an operand was expected");
  }

  while (!operators.empty()) {
    if (operators.top() == '(') {
      throw InvalidEquationStructure("Unbalanced parentheses: missing ')'");
    }
    reduce();
  }

  if (elements.size() != 1) {
    throw InvalidEquationStructure("Malformed expression");
  }

  unique_ptr<Element> result = std::move(elements.top());
  elements.pop();
  return result.release();
}

void Parser::next(const Token& token) {
  switch (token.type) {
    case TokenType::Operator: op(token.text);  break;
    case TokenType::Number:   num(token.text); break;
    case TokenType::LParen:   opnParen();      break;
    case TokenType::RParen:   closeParen();    break;
    case TokenType::Invalid:
      throw InvalidElement("Invalid token: " + token.text);
  }
}

void Parser::op(const string& text) {
  if (expectOperand) {
    throw InvalidEquationStructure("Unexpected operator " + text);
  }
  char incoming = text[0];

  while (!operators.empty() && operators.top() != '(' &&
         precedence(operators.top()) >= precedence(incoming)) {
    reduce();
  }
  operators.push(incoming);
  expectOperand = true;
}

void Parser::num(const string& text) {
  if (!expectOperand) {
    throw InvalidEquationStructure("Unexpected number " + text);
  }
  elements.push(make_unique<Element>(text));
  expectOperand = false;
}

void Parser::opnParen() {
  if (!expectOperand) {
    throw InvalidEquationStructure("Unexpected '('");
  }
  operators.push('(');
}

void Parser::closeParen() {
  if (expectOperand) {
    throw InvalidEquationStructure("Unexpected ')'");
  }
  while (!operators.empty() && operators.top() != '(') {
    reduce();
  }
  if (operators.empty()) {
    throw InvalidEquationStructure("Unbalanced parentheses: extra ')'");
  }
  operators.pop();
  expectOperand = false;
}
