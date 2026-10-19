#include "operation.h"
#include "element.h"
#include "exceptions.h"
#include <sstream>

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

Operation Operation::parseOperation(const string& element) {
  istringstream readable = istringstream(element);
  string lhs,op,rhs;

  if(!(readable >> lhs >> op >> rhs)) {
    throw InsufficientArgumentCount("Too few arguments in string " + element);
  }

  if (!(Element::canConvertToElement(lhs) )) {
    throw InvalidElement("lhs element " + lhs + " is invalid!");
  }
  if (!(Operator::is_operator(op))) {
    throw InvalidOperator("operator " + op + " is invalid!");
  }
  if (!(Element::canConvertToElement(rhs) )) {
    throw InvalidElement("rhs element " + rhs + " is invalid!");
  }
  return Operation(
    new Element(lhs),
    new Operator(op),
    new Element(rhs)
  );
}

Operation::Operation(const Operation& other)
  : lhs(other.lhs->clone()), 
    op (other.op ->clone()), 
    rhs(other.rhs->clone())
  { }

void swap(Operation& first, Operation& second) {
  swap(first.lhs, second.lhs);
  swap(first.op, second.op);
  swap(first.rhs, second.rhs);
}

Operation& Operation::operator=(Operation other) {
  swap(*this,other);
  return *this;
}
Operation::~Operation() {
  delete lhs;
  delete op;
  delete rhs;
}
ostream& operator<<(ostream& os, const Operation& op) {
    return os << "(" << op.lhs << " " << op.op << " " << op.rhs << ")";
}

Element Operation::compute() {
  return this->op->operate(*(this->lhs),*(this->rhs));
}

bool Operation::is_valid() {
  if (op->requires_nonzero_rhs()) {
    if (rhs->DoubleValue() == 0.0) {
      std::cerr << "Error: cannot divide by 0." << std::endl;
      return false;
    }
  }
  if (op->requires_int()) {
    if (this->lhs->IsDouble() || this->rhs->IsDouble()) {
      std::cerr << "Error: modulo operator requires integers only." << std::endl;
      return false;
    }
  }
  return true;
}
