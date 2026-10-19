#include "exceptions.h"
#include "operation.h"
#include "element.h"
#include <sstream>

using namespace std;

Operation Operation::parseOperation(const string& element) {
  istringstream readable = istringstream(element);
  string lhs_s,op_s,rhs_s;

  if(!(readable >> lhs_s >> op_s >> rhs_s)) {
    throw InsufficientArgumentCount("Too few arguments in string " + element);
  }

  if (!(Element::canConvertToElement(lhs_s) )) {
    throw InvalidElement("lhs element " + lhs_s + " is invalid!");
  }
  if (!(Operator::is_operator(op_s))) {
    throw InvalidOperator("operator " + op_s + " is invalid!");
  }
  if (!(Element::canConvertToElement(rhs_s) )) {
    throw InvalidElement("rhs element " + rhs_s + " is invalid!");
  }
  Element* lhs = new Element(lhs_s);
  Operator* op = new Operator(op_s);
  Element* rhs = new Element(rhs_s);

  Element computed = op->operate(*lhs, *rhs);
  return Operation(computed, lhs, op, rhs);
}

Operation::Operation(const Operation& other)
  : 
    Element(other),
    lhs(other.lhs->Clone()), 
    op (other.op ->Clone()), 
    rhs(other.rhs->Clone())
  { }

void swap(Operation& first, Operation& second) {
  swap(static_cast<Element&>(first), static_cast<Element&>(second));
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
    return os << "(" << *op.lhs << " " << *op.op << " " << *op.rhs << ")";
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
  return this->Value();
}
int Operation::IntValue() const {
  return this->IntValue();
}
double Operation::DoubleValue() const {
  return this->DoubleValue();
}
bool Operation::IsInt() const {
  return this->IsInt();
}
bool Operation::IsDouble() const {
  return this->IsDouble();
}
Operation* Operation::Clone() const {
  return new Operation(*this);
}
