#include<iostream>
#include<unordered_map>
#include<string_view>
#include<string>
#include<vector>

using namespace std::literals;

class Solution {
public:
    std::string numberToWords(int num) {
        const std::string number_digits = std::to_string(num);
        std::vector<std::string_view> reversed_res_seq;
        int counter = 0;
        auto it = number_digits.rbegin();
        auto end_it = number_digits.rend();

        while (it != end_it) {
            if (counter == 0) {
                ++counter;
            }
            else {
                reversed_res_seq.push_back(regs_[counter]);
                ++counter;
            }
            for (int i = 0; it != end_it; ++i, ++it) {
                int digit = *it - '0';
                if (i == 0) {
                    int next_digit = std::next(it) != end_it ? *std::next(it) - '0' : 0;
                    if (next_digit == 1) {
                        reversed_res_seq.push_back(ParseTeens(digit));
                        ++it;
                        ++i;
                        continue;
                    }
                    else {
                        if (digit == 0) {
                            continue;
                        }
                        reversed_res_seq.push_back(ParseDigit(digit));
                        continue;
                    }
                }
                if (i == 1) {
                    if (digit == 0) {
                        continue;
                    }
                    reversed_res_seq.push_back(ParseTens(digit));
                    continue;
                }
                if (i == 2) {
                    if (digit == 0) {
                        break;
                    }
                    reversed_res_seq.push_back(regs_[0]);
                    reversed_res_seq.push_back(ParseDigit(digit));
                    ++it;
                    break;
                }
            }
        }
        std::string result;
        bool IsFirst = true;
        for (auto str_it = reversed_res_seq.rbegin(); str_it != reversed_res_seq.rend(); ++str_it) {
            if (IsFirst) {
                IsFirst = false;
            }
            else {
                result += ' ';
            }
            result += std::string(*str_it);
        }
        return result;
    }

private:
    static inline const std::unordered_map<int, std::string_view> first_digits_{{1, "One"sv}, {2, "Two"sv}, {3, "Three"sv}, {4, "Four"sv}, {5, "Five"sv},
                                                                                {6, "Six"sv}, {7, "Seven"sv}, {8, "Eight"sv}, {9, "Nine"sv}};
    static inline const std::unordered_map<int, std::string_view> teens_{{0, "Ten"sv}, {1, "Eleven"sv}, {2, "Twelve"sv}, {3, "Thirteen"sv}, {4, "Fourteen"sv},
                                                                         {5, "Fifteen"sv}, {6, "Sixteen"sv}, {7, "Seventeen"sv}, {8, "Eighteen"sv}, {9, "Nineteen"sv}};
    static inline const std::unordered_map<int, std::string_view> tens_{{2, "Twenty"sv}, {3, "Thirty"sv}, {4, "Forty"}, {5, "Fifty"sv}, {6, "Sixty"sv},
                                                                        {7, "Seventy"sv}, {8, "Eighty"sv}, {9, "Ninety"sv}};
    static inline const std::string_view regs_[]{{"Hundred"sv}, {"Thousand"sv}, {"Million"sv}, {"Billion"sv}};

    std::string_view ParseDigit(int num) {
        return first_digits_.at(num);
    }

    std::string_view ParseTeens(int num) {
        return teens_.at(num);
    }

    std::string_view ParseTens(int num) {
        return tens_.at(num);
    }
};

int main() {
    Solution s;
    std::cout << s.numberToWords(1786333155) << '\n';
}