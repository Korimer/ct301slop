#include <iostream>
#include <typeinfo>
#include "element.h"
#include "operator.h"
#include "operation.h"
#include "exceptions.h"

using namespace std;

int main() {
    cout << boolalpha;

    // Test 1: Addition (Int + Int)
    cout << "(10 + 20) = 30";
    try {
        Operation op1("10 + 20");
        cout << "\t" << op1 << " = " << op1.Value();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    cout << "The value is a double: false";
    try {
        Operation op1("10 + 20");
        cout << "\tThe value is a double: " << op1.IsDouble();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    // Test 2: Subtraction (Double - Double)
    cout << "(15.5 - 5.5) = 10";
    try {
        Operation op2("15.5 - 5.5");
        cout << "\t" << op2 << " = " << op2.Value();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    cout << "The value is a double: true";
    try {
        Operation op2("15.5 - 5.5");
        cout << "\tThe value is a double: " << op2.IsDouble();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    // Test 3: Multiplication (Int * Int)
    cout << "(3 * 4) = 12";
    try {
        Operation op3("3 * 4");
        cout << "\t" << op3 << " = " << op3.Value();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    cout << "The value is a double: false";
    try {
        Operation op3("3 * 4");
        cout << "\tThe value is a double: " << op3.IsDouble();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    // Test 4: Division (Int / Int)
    cout << "(10 / 4) = 2";
    try {
        Operation op4("10 / 4");
        cout << "\t" << op4 << " = " << op4.Value();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    cout << "The value is a double: false";
    try {
        Operation op4("10 / 4");
        cout << "\tThe value is a double: " << op4.IsDouble();
    } catch (const exception& e) {
        cout << "\tError: " << e.what();
    }
    cout << "\n";

    // Test 6: Modulo by double (capturing the actual exception thrown)
    cout << "(17 % 4.6) = 1";
    try {
        Operation op5("17 % 4.6");
        cout << "\t" << op5 << " = " << op5.Value() << endl;
    } catch (const exception& e) {
        cout << "~~ what(): " << e.what() << "~~\n";
    }

    return 0;
}
