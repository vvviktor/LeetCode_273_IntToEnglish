#include<iostream>
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
        bool AllZeros = true;

        while (it != end_it) {
            if (counter == 0) {
                ++counter;
            }
            else {
                if (AllZeros && counter > 1) {
                    reversed_res_seq.pop_back();
                }
                else {
                    AllZeros = true;
                }
                reversed_res_seq.push_back(regs_[counter]);
                ++counter;
            }
            for (int i = 0; it != end_it; ++i, ++it) {
                int digit = *it - '0';
                if (i == 0) {
                    if (std::next(it) == end_it && digit == 0) {
                        reversed_res_seq.push_back(ParseDigit(digit));
                    }
                    int next_digit = std::next(it) != end_it ? *std::next(it) - '0' : 0;
                    if (next_digit == 1) {
                        AllZeros = false;
                        reversed_res_seq.push_back(ParseTeens(digit));
                        ++it;
                        ++i;
                        continue;
                    }
                    else {
                        if (digit == 0) {
                            continue;
                        }
                        AllZeros = false;
                        reversed_res_seq.push_back(ParseDigit(digit));
                        continue;
                    }
                }
                if (i == 1) {
                    if (digit == 0) {
                        continue;
                    }
                    AllZeros = false;
                    reversed_res_seq.push_back(ParseTens(digit));
                    continue;
                }
                if (i == 2) {
                    if (digit == 0) {
                        ++it;
                        break;
                    }
                    AllZeros = false;
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
    static inline const char* first_digits_[]{"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    static inline const char* teens_[]{"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    static inline const char* tens_[]{"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    static inline const char* regs_[]{"Hundred", "Thousand", "Million", "Billion"};

    std::string_view ParseDigit(int num) {
        return first_digits_[num];
    }

    std::string_view ParseTeens(int num) {
        return teens_[num];
    }

    std::string_view ParseTens(int num) {
        return tens_[num];
    }
};

int main() {
    Solution s;
    std::cout << s.numberToWords(1000056901) << '\n';
}