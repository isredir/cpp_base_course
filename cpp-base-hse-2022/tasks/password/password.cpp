#include "password.h"
#include <cctype>

bool ValidatePassword(const std::string& password) {
    if (password.size() < 8 || password.size() > 14) {
        return false;
    } else {
        int upper = 0, lower = 0, digits = 0, others = 0;
        for (size_t i = 0; i < password.size(); ++i) {
            if (password[i] < 33 || password[i] > 126) {
                return false;
            } else {
                if (std::isupper(password[i])) {
                    upper = 1;
                } else if (std::islower(password[i])) {
                    lower = 1;
                } else if (std::isdigit(password[i])) {
                    digits = 1;
                } else {
                    others = 1;
                }
            }
        }
        if (upper + lower + digits + others < 3) {
            return false;
        }
    }
    return true;
}
