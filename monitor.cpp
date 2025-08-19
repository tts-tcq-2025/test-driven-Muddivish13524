// monitor.cpp
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

// Define vital limits
struct Limits {
    int min;
    int max;
};

std::map<std::string, Limits> VITAL_LIMITS = {
    {"temperature", {95, 102}},
    {"pulseRate", {60, 100}},
    {"spo2", {90, 100}}
};

// Message map
std::map<std::string, std::string> messages = {
    {"temperature", "Temperature critical!"},
    {"pulseRate", "Pulse Rate is out of range!"},
    {"spo2", "Oxygen Saturation out of range!"}
};

// Check if value is within limits
bool is_within_limits(int value, const Limits& limits) {
    return limits.min <= value && value <= limits.max;
}

// Check vitals and collect failed messages
std::vector<std::pair<std::string, std::string>> check_vitals(const std::map<std::string, int>& vitals) {
    std::vector<std::pair<std::string, std::string>> failed;
    for (const auto& pair : vitals) {
        const std::string& vital = pair.firs
