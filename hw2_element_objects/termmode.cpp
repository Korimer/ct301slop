#include "./utils.h"
#include <cstdlib>
#include <optional>
#include <string>

typedef BasicOperator BOp;

using namespace std;

Operation convert_or_exit(string lhs, string op, string rhs) {
  optional<Element> opt_lhs = convertToElement(lhs);
  if (!opt_lhs.has_value()) {
    std::cerr << "Error parsing lhs value " << lhs << std::endl;
    exit(3);
  }

  optional<BOp> opt_op;
  if (!BOp::is_operator(op)) {
    std::cerr << "Error parsing operator value " << op << std::endl;
    exit(4);
  }
  else {
    opt_op = BOp(op);
  }

  optional<Element> opt_rhs = convertToElement(rhs);
  if (!opt_rhs.has_value()) {
    std::cerr << "Error parsing operator value " << rhs << std::endl;
    exit(5);
  }

  return Operation(opt_lhs.value(), opt_op.value(), opt_rhs.value());
}
