#include "gtest/gtest.h"
#include "../StringCalculator.h"

TEST(StringCalculatorTest, EmptyStringReturnsZero) {
    StringCalculator calc;
    EXPECT_EQ(calc.Add(""), 0);
}
