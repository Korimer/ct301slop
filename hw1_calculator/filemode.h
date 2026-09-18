# pragma once
# include "./utils.h"
# include <optional>
# include <string>

std::optional<Operation> triad_to_opr(std::string lhs, std::string op, std::string rhs);
