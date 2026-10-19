#include "element.h"
#include "operator.h"
#include <stdexcept>
#include <string>

using namespace std;

Operator::Operator(string op) {
  if (!Operator::is_operator(op)) {
    throw runtime_error("provided operator not one of +-*/");
  }
  else {
    this->chr = op;
  }
}
bool Operator::is_operator(string chr) {
  return
       chr == "+"
    || chr == "-"
    || chr == "*"
    || chr == "/"
    || chr == "%"
  ;
}
Element Operator::operate(Element lhs, Element rhs) {
  if (chr == "+") { return lhs + rhs; }
  if (chr == "-") { return lhs - rhs; }
  if (chr == "*") { return lhs * rhs; }
  if (chr == "/") { return lhs / rhs; }
  if (chr == "%") { return lhs % rhs; }
  throw runtime_error("impossible state: operator not one of +-*/");
}

bool Operator::requires_nonzero_rhs() {
  return chr == "/" || chr == "%";
}
bool Operator::requires_int() {
  return chr == "%";
}
