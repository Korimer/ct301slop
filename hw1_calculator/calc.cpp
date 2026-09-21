#include "./filemode.h"
#include "./termmode.h"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[] ) {
  vector<Operation> all_oprs;

  if (argc == 1) {
    std::cout << "misuse" << std::endl;
    return 1; 
  }
  else if (argc == 2) {
    ifstream file = ifstream(argv[1]);
    if (!file.is_open()) {
      std::cerr << "File could not be opened." << std::endl;
      exit(2);
    }
    int line_count = 1;
    string line;
    while (getline(file, line)) {
      // credit to https://stackoverflow.com/a/61005054
      if (line.size() == 0) {
        continue;
      }
      optional<Operation> opr = lineToOperation(line);
      if (opr.has_value()) {
        if (!opr.value().is_valid()) {
          exit(line_count+2);
        }
        all_oprs.push_back(opr.value());
        line_count++;
      }
      else {
        if (!file.eof()) {
          std::cerr << "Exited prematurely due to error on line " << line_count << std::endl;
          exit(line_count+2);
        }
        break;
      }
    }
  }
  else if (argc == 4) {
    Operation opr_convert = convert_or_exit(argv[1], argv[2], argv[3]);
    if (!opr_convert.is_valid()) {
      exit(4);
    }
    all_oprs.push_back(opr_convert);
  }
  else {
    std::cerr << "Incorrect argument count. Submit 0, 1, or 3.";
    exit(2);
  }

  for (size_t i=0; i<all_oprs.size(); i++) {
    all_oprs[i].compute().print();
  }

  return 0;
} 
