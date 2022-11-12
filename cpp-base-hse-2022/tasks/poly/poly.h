#pragma once

#include <vector>
#include <map>
#include <cstdint>
#include <ostream>

class Poly {
public:
    Poly();
    Poly(const std::map<int64_t, int64_t>& coefs);
    Poly(const std::vector<int64_t>& coefs);
    int64_t operator()(const int64_t x) const;
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;
    Poly operator+(const Poly& other) const;
    Poly operator-() const;
    Poly operator-(const Poly& other) const;
    Poly operator+=(const Poly& other);
    Poly operator-=(const Poly& other);
    Poly operator*(const Poly& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Poly& poly);

private:
    std::map<int64_t, int64_t> coefs_;
};
