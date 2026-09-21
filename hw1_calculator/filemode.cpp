#include "./utils.h"

#include <fstream>

optional<Operation> triadToOpr(string lhs, string op, string rhs) {
  optional<Number> lhs_convert = convertToNumber(lhs);
  optional<BasicOperator> op_convert = convertToBasicOperation(op);
  optional<Number> rhs_convert = convertToNumber(rhs);
  if (lhs_convert.has_value() && op_convert.has_value() && rhs_convert.has_value()) {
    Operation operation = Operation(lhs_convert.value(), op_convert.value(), rhs_convert.value());
    return optional<Operation>(operation);
  }
  else {
    return std::nullopt;
  }
}

optional<Operation> lineToOperation(std::ifstream& file) {
  string lhs, op, rhs;
  try {
    file >> lhs;
    file >> op;
    file >> rhs;
    return triadToOpr(lhs, op, rhs);
  } catch (...) {
    return nullopt;
  }
}
