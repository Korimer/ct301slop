# pragma once
# include <optional>
# include <string>

using namespace std;

class BasicOperator {
  private:
    string chr;
  public:
    BasicOperator(string op);
    static bool is_operator(string chr);
    int operate(int lhs, int rhs);
};

class Operation {
  private:
    int lhs;
    BasicOperator op;
    int rhs;

  public:
    Operation(int lhs, BasicOperator op, int rhs):
      lhs(lhs), op(op), rhs(rhs) {}
    int compute();
};

optional<int> optional_stoi(string s);
optional<BasicOperator> optional_sto_bopr(string s);
