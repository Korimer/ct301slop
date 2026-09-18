#include "./utils.h"
#include <cstdlib>
#include <optional>
#include <string>

typedef BasicOperator BOp;

Operation convert_or_exit(string lhs, string op, string rhs) {
  optional<int> opt_lhs = optional_stoi(lhs);
  if (!opt_lhs.has_value()) {
    exit(3);
  }

  optional<BOp> opt_op;
  if (!BOp::is_operator(op)) {
    exit(4);
  }
  else {
    opt_op = BOp(op);
  }

  optional<int> opt_rhs = optional_stoi(rhs);
  if (!opt_rhs.has_value()) {
    exit(5);
  }

  return Operation(opt_lhs.value(), opt_op.value(), opt_rhs.value());
}
