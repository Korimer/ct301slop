#pragma once

#include "element.h"
#include "operator.h"
#include <string>

class Operation {
  private:
    Element* lhs;
    Operator* op;
    Element* rhs;

    Operation(Element* lhs, Operator* op, Element* rhs):
      lhs(lhs), op(op), rhs(rhs) {};

    static Operation parseOperation(const std::string& element);

    friend void swap(Operation& first, Operation& second);
  public:
    Operation(const std::string& element):
      Operation(parseOperation(element)) {};

    Operation(const Element& leftElem, char opChar, const Element& rightElem);
    
    // Rule of Three / Big Three implementation
    Operation(const Operation& other);
    Operation& operator= (Operation other);
    virtual ~Operation();

    friend std::ostream& operator<<(std::ostream&, const Operation&);

    Element compute();
    bool is_valid();
};
