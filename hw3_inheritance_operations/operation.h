# pragma once

#include "element.h"
#include "operator.h"
#include <string>

class Operation {
  private:
    Element lhs;
    Operator op;
    Element rhs;
  public:
    Operation(const std::string& element);
    Operation(const Element& leftElem, char op, const Element& rightElem);
    Operation(const Operation& other);
    Operation& operator= (Operation other);
    virtual ~Operation();
    friend std::ostream& operator<<(std::ostream&, const Operation&);

    Element compute();
    bool is_valid();
};
