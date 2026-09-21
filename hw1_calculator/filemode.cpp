#include "./utils.h"

#include <fstream>

optional<Operation> triadToOpr(string lhs, string op, string rhs) {
  optional<int> lhs_convert = optional_stoi(lhs);
  optional<BasicOperator> op_convert = optional_sto_bopr(op);
  optional<int> rhs_convert = optional_stoi(rhs);
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
