#include "./utils.h"

#include <sstream>

using namespace std;

std::optional<Operation> triadToOpr(std::string lhs, std::string op, std::string rhs) {
  std::optional<Element> lhs_convert = convertToElement(lhs);
  std::optional<BasicOperator> op_convert = convertToBasicOperation(op);
  std::optional<Element> rhs_convert = convertToElement(rhs);
  if (lhs_convert.has_value() && op_convert.has_value() && rhs_convert.has_value()) {
    Operation operation = Operation(lhs_convert.value(), op_convert.value(), rhs_convert.value());
    return std::optional<Operation>(operation);
  }
  else {
    return std::nullopt;
  }
}

// Thanks to https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
std::optional<Operation> lineToOperation(std::string line) {
  std::stringstream sstream = std::stringstream(line);
  std::string lhs, op, rhs;
  try {
    sstream >> lhs;
    sstream >> op;
    sstream >> rhs;
    return triadToOpr(lhs, op, rhs);
  } catch (...) {
    return std::nullopt;
  }
}
