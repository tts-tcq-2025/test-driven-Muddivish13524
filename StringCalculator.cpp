#include "StringCalculator.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <regex>

using namespace std;

int StringCalculator::add(const string& numbers) {
    if (numbers.empty()) return 0;

    string delimiters = ",|\n"; // default delimiters
    string nums = numbers;

    // Check for custom delimiter
    if (numbers.substr(0, 2) == "//") {
        size_t newlinePos = numbers.find('\n');
        string delimiterSection = numbers.substr(2, newlinePos - 2);

        vector<string> customDelimiters;

        if (!delimiterSection.empty() && delimiterSection.front() == '[') {
            regex re(R"(\[(.*?)\])");
            auto words_begin = sregex_iterator(delimiterSection.begin(), delimiterSection.end(), re);
            auto words_end = sregex_iterator();

            for (auto i = words_begin; i != words_end; ++i) {
                smatch match = *i;
                customDelimiters.push_back(match.str(1));
            }
        } else {
            customDelimiters.push_back(delimiterSection);
        }

        delimiters = "";
        for (const auto& d : customDelimiters) {
            if (!delimiters.empty()) delimiters += "|";
            delimiters += regex_replace(d, regex(R"([\^$.|?*+()\\])"), R"(\\$&)");
        }

        nums = numbers.substr(newlinePos + 1);
    }

    regex re_delim(delimiters);
    sregex_token_iterator iter(nums.begin(), nums.end(), re_delim, -1);
    sregex_token_iterator end;

    vector<int> negatives;
    int sum = 0;

    for (; iter != end; ++iter) {
        string token = iter->str();
        if (token.empty()) continue;

        int num = stoi(token);
        if (num < 0) {
            negatives.push_back(num);
        } else if (num <= 1000) {
            sum += num;
        }
    }

    if (!negatives.empty()) {
        string message = "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            message += to_string(negatives[i]);
            if (i != negatives.size() - 1) message += ", ";
        }
        throw runtime_error(message);
    }

    return sum;
}
