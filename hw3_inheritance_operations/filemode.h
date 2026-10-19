# pragma once
# include "./utils.h"
# include <optional>
# include <string>

std::optional<Operation> lineToOperation(std::string stream);
