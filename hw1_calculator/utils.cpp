#include "utils.h"

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
  ;
}
int BasicOperator::operate(int lhs, int rhs) {
  if (chr == "+") { return lhs + rhs; }
  if (chr == "-") { return lhs - rhs; }
  if (chr == "*") { return lhs * rhs; }
  if (chr == "/") { return lhs / rhs; }
  throw runtime_error("impossible state: operator not one of +-*/");
}

int Operation::compute() {
  return this->op.operate(this->lhs,this->rhs);
}

optional<int> optional_stoi(string s) {
  optional<int> option;
  try {
    int as_int = stoi(s);
    return optional<int>(as_int);
  } catch (...) {
    return std::nullopt;
  }
}

optional<BasicOperator> optional_sto_bopr(string s) {
  if (s.length() == 1 && BasicOperator::is_operator(s)) {
    return BasicOperator(s);
  }
  return nullopt;
}
