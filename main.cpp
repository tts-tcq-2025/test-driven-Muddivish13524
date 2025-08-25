#include <iostream>
#include <stdexcept>
#include "StringCalculator.h"

using namespace std;

void assertEqual(int actual, int expected, const string& testName) {
    if (actual == expected) {
        cout << "[PASS] " << testName << endl;
    } else {
        cout << "[FAIL] " << testName << ": Expected " << expected << ", but got " << actual << endl;
    }
}

void assertThrows(const string& input, const string& expectedMessage, const string& testName) {
    try {
        StringCalculator::add(input);
        cout << "[FAIL] " << testName << ": Expected exception but none thrown" << endl;
    } catch (const runtime_error& e) {
        string actualMessage = e.what();
        if (actualMessage == expectedMessage) {
            cout << "[PASS] " << testName << endl;
        } else {
            cout << "[FAIL] " << testName << ": Expected exception message '" << expectedMessage
                 << "' but got '" << actualMessage << "'" << endl;
        }
    } catch (...) {
        cout << "[FAIL] " << testName << ": Unexpected exception type thrown" << endl;
    }
}

int main() {
    assertEqual(StringCalculator::add(""), 0, "Empty string returns 0");
    assertEqual(StringCalculator::add("1"), 1, "Single number returns itself");
    assertEqual(StringCalculator::add("1,2"), 3, "Two numbers comma delimited");
    assertEqual(StringCalculator::add("1,2,3,4,5"), 15, "Multiple numbers");
    assertEqual(StringCalculator::add("1\n2,3"), 6, "New lines between numbers");
    assertEqual(StringCalculator::add("//;\n1;2"), 3, "Custom delimiter ';'");
    assertThrows("-1", "negatives not allowed: -1", "Single negative number exception");
    assertThrows("2,-4,3,-5", "negatives not allowed: -4, -5", "Multiple negative numbers exception");
    assertEqual(StringCalculator::add("2,1001"), 2, "Ignore numbers > 1000");
    assertEqual(StringCalculator::add("//[***]\n1***2***3"), 6, "Delimiter of any length");
    assertEqual(StringCalculator::add("//[*][%]\n1*2%3"), 6, "Multiple delimiters");

    return 0;
}
