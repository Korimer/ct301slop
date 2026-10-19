#include "element.h"
#include "operator.h"
#include <stdexcept>
#include <string>

using namespace std;

Operator::Operator(char op):
  chr(op)
{
  if (!is_operator(op)) {
    throw std::invalid_argument("Invalid operator character");
  }
}

char Operator::toChar(std::string op) {
  if (op.length() != 1) {
    throw std::invalid_argument("Invalid operator string");
  }
  char chr = op[0];
  return chr;
}

bool Operator::is_operator(const char& chr) {
  return
    chr == '+'
    || chr == '-'
    || chr == '*'
    || chr == '/'
    || chr == '%'
    ;
}

bool Operator::is_operator(const string& str) {
  try {
    return is_operator(toChar(str));
  } catch (invalid_argument&) {
    return false;
  }
}
Element Operator::operate(const Element& lhs, const Element& rhs) {
  if (chr == '+') { return lhs + rhs; }
  if (chr == '-') { return lhs - rhs; }
  if (chr == '*') { return lhs * rhs; }
  if (chr == '/') { return lhs / rhs; }
  if (chr == '%') { return lhs % rhs; }
  throw runtime_error("impossible state: operator not one of +-*/");
}

Operator* Operator::clone() const {
  return new Operator(*this);
}

bool Operator::requires_nonzero_rhs() {
  return chr == '/' || chr == '%';
}
bool Operator::requires_int() {
  return chr == '%';
}

ostream& operator<<(ostream& os, const Operator& op) {
    return os << string(1,op.chr);
}
