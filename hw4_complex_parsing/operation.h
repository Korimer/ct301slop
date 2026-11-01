#pragma once

#include "element.h"
#include "operator.h"
#include <string>

class Operation : public Element {
  private:
    Element* lhs;
    Operator* op;
    Element* rhs;

    Operation(Element computed, Element* lhs, Operator* op, Element* rhs):
      Element(computed), lhs(lhs), op(op), rhs(rhs) {};

    static Operation parseOperation(const std::string& element);

    friend void swap(Operation& first, Operation& second);
  public:
    Operation(const std::string& element):
      Operation(parseOperation(element)) {};

    Operation(const Element& leftElem, Operator opChar, const Element& rightElem):
      Element(opChar.operate(leftElem, rightElem)),
      lhs(new Element(leftElem)), op(new Operator(opChar)), rhs(new Element(rightElem))
      {};

    Operation(const Operation& other);
    Operation& operator= (Operation other);
    virtual ~Operation();

    friend std::ostream& operator<<(std::ostream&, const Operation&);

    virtual double Value() const override;
    virtual int IntValue() const override;
    virtual double DoubleValue() const override;
    virtual bool IsDouble() const override;
    virtual bool IsInt() const override;
    virtual Operation* Clone() const override;

    Element compute() const;
    void check_valid() const;
};
