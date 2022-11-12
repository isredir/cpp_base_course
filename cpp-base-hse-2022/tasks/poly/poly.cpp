#include "poly.h"

Poly::Poly() : coefs_({}) {
}

Poly::Poly(const std::map<int64_t, int64_t>& coefs) : coefs_(coefs) {
}

Poly::Poly(const std::vector<int64_t>& coefs) {
    int64_t deg = 0;
    for (int64_t num : coefs) {
        if (num != 0) {
            coefs_[deg] = num;
        }
        ++deg;
    }
}

int64_t Poly::operator()(const int64_t x) const {
    int64_t res = 0;
    int64_t mult = 1;
    int64_t deg_x = 0;
    for (auto [deg, coef] : coefs_) {
        for (int64_t i = deg_x; i < deg; ++i) {
            mult *= x;
        }
        deg_x = deg;
        res += coef * mult;
    }
    return res;
}

bool Poly::operator==(const Poly& other) const {
    if (coefs_.size() != other.coefs_.size()) {
        return false;
    }
    for (auto [deg, coef] : coefs_) {
        auto it = other.coefs_.find(deg);
        if (it == other.coefs_.end() || coef != it->second) {
            return false;
        }
    }
    return true;
}

bool Poly::operator!=(const Poly& other) const {
    return !(*this == other);
}

Poly Poly::operator+(const Poly& other) const {
    Poly res;
    for (auto [deg, coef] : coefs_) {
        auto it = other.coefs_.find(deg);
        if (it != other.coefs_.end() && coef + it->second != 0) {
            res.coefs_[deg] = coef + it->second;
        }
    }
    return res;
}

Poly Poly::operator-() const {
    Poly res;
    for (auto [deg, coef] : coefs_) {
        res.coefs_[deg] = -coef;
    }
    return res;
}

Poly Poly::operator-(const Poly& other) const {
    return *this + (-other);
}

Poly Poly::operator+=(const Poly& other) {
    *this = *this + other;
    return *this;
}

Poly Poly::operator-=(const Poly& other) {
    *this = *this - other;
    return *this;
}

Poly Poly::operator*(const Poly& other) const {
    Poly res;
    for (auto [deg1, coef1] : coefs_) {
        for (auto [deg2, coef2] : other.coefs_) {
            res.coefs_[deg1 + deg2] += coef1 * coef2;
        }
    }
    return res;
}

std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    if (poly.coefs_.empty()) {
        out << "y = 0";
        return out;
    }
    std::string res = "y = ";
    size_t pos = 0;
    for (auto it = poly.coefs_.rbegin(); it != poly.coefs_.rend(); ++it) {
        auto [deg, coef] = *it;
        res += std::to_string(coef);
        if (deg > 0) {
            res += "x^" + std::to_string(deg);
        }
        if (pos < poly.coefs_.size() - 1) {
            res += " + ";
        }
        ++pos;
    }
    out << res;
    return out;
}
