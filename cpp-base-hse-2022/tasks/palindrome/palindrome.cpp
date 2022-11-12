#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    std::string str1;
    std::string str2;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            str1 += str[i];
            str2 = str[i] + str2;
        }
    }
    return (str2 == str1);
}
