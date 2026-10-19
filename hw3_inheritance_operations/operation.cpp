#include "exceptions.h"
#include "operation.h"
#include "element.h"
#include <sstream>

using namespace std;

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
  : 
    Element(other),
    lhs(other.lhs->Clone()), 
    op (other.op ->Clone()), 
    rhs(other.rhs->Clone())
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

Element Operation::compute() const {
  this->check_valid();
  return this->op->operate(*(this->lhs),*(this->rhs));
}

void Operation::check_valid() const {
  if (op->requires_nonzero_rhs()) {
    if (rhs->DoubleValue() == 0.0) {
      throw DivideByZeroError("Error: cannot divide by 0.");
    }
  }
  if (op->requires_int()) {
    if (this->lhs->IsDouble() || this->rhs->IsDouble()) {
      throw ModuloByDoubleError("Error: modulo operator requires integers only.");
    }
  }
}

// Bro...

double Operation::Value() const {
  return this->compute().Value();
}
int Operation::IntValue() const {
  return this->compute().IntValue();
}
double Operation::DoubleValue() const {
  return this->compute().DoubleValue();
}
bool Operation::IsDouble() const {
  return this->compute().IsDouble();
}
Operation* Operation::Clone() const {
  return new Operation(*this);
}
