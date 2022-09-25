#include<iostream>
#include<string>

using namespace std::literals;

class Solution {
public:
    std::string numberToWords(int num) {
        if (num == 0) {
            return first_digits_[num];
        }

        return RecursiveHelper(num);
    }

private:
    static inline const char* first_digits_[]{"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    static inline const char* teens_[]{"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    static inline const char* tens_[]{"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    static inline const char* regs_[]{"Hundred", "Thousand", "Million", "Billion"};

    std::string RecursiveHelper(int num) {
        if (num >= 1000000000) {
            int rest = num % 1000000000;
            return {RecursiveHelper(num / 1000000000) + ' ' + regs_[3] + (rest != 0 ? ' ' + RecursiveHelper(rest) : ""s)};
        }
        if (num >= 1000000) {
            int rest = num % 1000000;
            return {RecursiveHelper(num / 1000000) + ' ' + regs_[2] + (rest != 0 ? ' ' + RecursiveHelper(rest) : ""s)};
        }
        if (num >= 1000) {
            int rest = num % 1000;
            return {RecursiveHelper(num / 1000) + ' ' + regs_[1] + (rest != 0 ? ' ' + RecursiveHelper(rest) : ""s)};
        }
        if (num >= 100) {
            int rest = num % 100;
            return {RecursiveHelper(num / 100) + ' ' + regs_[0] + (rest != 0 ? ' ' + RecursiveHelper(rest) : ""s)};
        }
        if (num >= 20) {
            int rest = num % 10;
            return {std::string(tens_[num / 10]) + (rest != 0 ? ' ' + RecursiveHelper(rest) : ""s)};
        }
        if (num >= 10) {
            return {std::string(teens_[num % 10])};
        }
        else {
            return {std::string(first_digits_[num])};
        }
    }
};

int main() {
    Solution s;
    std::cout << s.numberToWords(50868) << '\n';
}