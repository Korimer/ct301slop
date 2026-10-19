#include "utils.h"
#include "element.h"

#include <stdexcept>
#include <string>
#include <optional>

using namespace std;



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
