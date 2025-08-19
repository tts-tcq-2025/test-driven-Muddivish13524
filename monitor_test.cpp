// monitor_test.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <utility>
#include <map>

// Include your monitor logic (assumes the functions are in monitor.cpp and declared in a header)
#include "monitor.h"  // You should create a header file exposing handle_vitals, vitals_ok, etc.

// Test temperature vital logic
TEST(MonitorTest, TemperatureCheck) {
    struct TestCase {
        int temp;
        int pulse;
        int spo2;
        bool expected_ok;
        std::string expected_msg;
    };

    std::vector<TestCase> cases = {
        {94, 80, 95, false, "Temperature critical!"},
        {103, 80, 95, false, "Temperature critical!"},
        {95, 80, 95, true, ""},
        {102, 80, 95, true, ""}
    };

    for (const auto& test : cases) {
        std::map<std::string, int> vitals = {
            {"temperature", test.temp},
            {"pulseRate", test.pulse},
            {"spo2", test.spo2}
        };
        std::vector<std::pair<std::string, std::string>> failed;
        bool ok = vitals_ok(vitals, failed);

        EXPECT_EQ(ok, test.expected_ok);
        if (!test.expected_ok) {
            bool found = false;
            for (const auto& pair : failed) {
                if (pair.fi
