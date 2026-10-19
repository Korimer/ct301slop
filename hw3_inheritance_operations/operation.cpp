#include "operation.h"

using namespace std;

optional<Element> convertToElement(string s) {
  if (Element::canConvertToElement(s)) {
    return Element(s);
  }
  return nullopt;
}

optional<Operator> convertToBasicOperation(string s) {
  if (s.length() == 1 && Operator::is_operator(s)) {
    return Operator(s);
  }
  return nullopt;
}

Operation::Operation(const string& element) {
  

}
Operation::Operation(const Element& leftElem, char op, const Element& rightElem) {

}
Operation::Operation(const Operation& other) {

}
Operation& Operation::operator=(Operation other) {

}
Operation::~Operation() {

}
ostream& operator<<(ostream& os, const Operation& op) {
    return os;
}


Element Operation::compute() {
  return this->op.operate(this->lhs,this->rhs);
}

bool Operation::is_valid() {
  if (op.requires_nonzero_rhs()) {
    if (rhs.DoubleValue() == 0.0) {
      std::cerr << "Error: cannot divide by 0." << std::endl;
      return false;
    }
  }
  if (op.requires_int()) {
    if (this->lhs.IsDouble() || this->rhs.IsDouble()) {
      std::cerr << "Error: modulo operator requires integers only." << std::endl;
      return false;
    }
  }
  return true;
}
