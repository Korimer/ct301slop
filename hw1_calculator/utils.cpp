#include "utils.h"
#include "number.h"

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
Number BasicOperator::operate(Number lhs, Number rhs) {
  if (chr == "+") { return lhs + rhs; }
  if (chr == "-") { return lhs - rhs; }
  if (chr == "*") { return lhs * rhs; }
  if (chr == "/") { return lhs / rhs; }
  if (chr == "%") { return lhs % rhs; }
  throw runtime_error("impossible state: operator not one of +-*/");
}

Number Operation::compute() {
  return this->op.operate(this->lhs,this->rhs);
}

optional<Number> convertToNumber(string s) {
  regex intregex = regex("^\\d+$");
  regex floatregex = regex("^\\d*\\.\\d+$");

  if (regex_match(s, intregex)) {
    int as_int = stoi(s);
    return optional<int>(as_int);
  }
  if (regex_match(s, floatregex)) {
    float as_float = stof(s);
    return Number(as_float);
  }
  else {
    return std::nullopt;
  }
}

optional<BasicOperator> convertToBasicOperation(string s) {
  if (s.length() == 1 && BasicOperator::is_operator(s)) {
    return BasicOperator(s);
  }
  return nullopt;
}
