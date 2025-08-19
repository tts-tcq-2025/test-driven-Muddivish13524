#include "StringCalculator.h"
#include <cassert>
#include <iostream>

void test_empty_string_returns_zero() {
    StringCalculator calc;
    assert(calc.Add("") == 0);
    std::cout << "✅ test_empty_string_returns_zero passed\n";
}

int main() {
    test_empty_string_returns_zero();
    return 0;
}
