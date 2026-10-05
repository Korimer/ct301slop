#include "utils.h"
#include "element.h"

#include <regex>
#include <stdexcept>
#include <string>
#include <optional>

using namespace std;

BasicOperator::BasicOperator(string op) {
  if (!BasicOperator::is_operator(op)) {
    throw runtime_error("provided operator not one of +-*/");
  }
  else {
    this->chr = op;
  }
}
bool BasicOperator::is_operator(string chr) {
  return chr == "+"
    || chr == "-"
    || chr == "*"
    || chr == "/"
    || chr == "%"
  ;
}
Element BasicOperator::operate(Element lhs, Element rhs) {
  if (chr == "+") { return lhs + rhs; }
  if (chr == "-") { return lhs - rhs; }
  if (chr == "*") { return lhs * rhs; }
  if (chr == "/") { return lhs / rhs; }
  if (chr == "%") { return lhs % rhs; }
  throw runtime_error("impossible state: operator not one of +-*/");
}

Element Operation::compute() {
  return this->op.operate(this->lhs,this->rhs);
}
bool Operation::is_valid() {
  if (this->op.chr == "/") {
    if ((this->rhs.IsInt() && rhs.getInt() == 0)
        || (this->rhs.IsFloat() && rhs.getFloat() == 0.0))
    {
      std::cerr << "Error: cannot divide by 0." << std::endl;
      return false;
    }
  }
  if (this->op.chr == "%") {
    if (this->lhs.IsFloat() || this->rhs.IsFloat()) {
      std::cerr << "Error: modulo operator requires integers only." << std::endl;
      return false;
    }
  }
  return true;
}


optional<Element> convertToElement(string s) {
  if (Element::canConvertToElement(s)) {
    return Element(s);
  }
  return nullopt;
}

optional<BasicOperator> convertToBasicOperation(string s) {
  if (s.length() == 1 && BasicOperator::is_operator(s)) {
    return BasicOperator(s);
  }
  return nullopt;
}
