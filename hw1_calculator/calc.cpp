#include "./filemode.h"
#include "./termmode.h"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
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
    int line_count = 1;
    string lhs, op, rhs;
    while (file >> lhs >> op >> rhs) {
      try {
        optional<Operation> opr_convert = triad_to_opr(lhs, op, rhs);
        all_oprs.push_back(opr_convert.value());
        line_count++;
      } catch (...) {
        exit(line_count+2);
      }
    }
  }
  else if (argc == 4) {
    Operation opr_convert = convert_or_exit(argv[1], argv[2], argv[3]);
    all_oprs.push_back(opr_convert);
  }

  for (size_t i=0; i<all_oprs.size(); i++) {
    cout << all_oprs[i].compute() << endl;
  }

  return 0;
} 
