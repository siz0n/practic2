#include <vector>
#include <iostream>
#include <cstdint>
#include "math.h"
#include "crypto.h"

using namespace std;
vector<pair<uint64_t, uint64_t >> encrypt(const string& message, uint64_t p, uint64_t k, uint64_t g, uint64_t y) {
    vector<pair<uint64_t, uint64_t>> encrypted;
    for (char c : message) {
        uint64_t m = static_cast<long long>(static_cast<unsigned char>(c)); 
        uint64_t a = fast_pow(g, k, p);
        uint64_t b = (fast_pow(y, k, p) * m) % p;
        encrypted.emplace_back(a, b);
    }
    return encrypted;
}
// Функция дешифрования
string decrypt(const vector<pair<uint64_t, uint64_t>>& encrypted, uint64_t p, uint64_t x) {
    string decrypted;
    for (const auto& pair : encrypted) {
        uint64_t a = pair.first;
        uint64_t b = pair.second;
        uint64_t exponent = p - 1 - x;
        uint64_t a_pow = fast_pow(a, exponent, p);
        uint64_t m = (b * a_pow) % p;
        decrypted += static_cast<char>(m);
    }
    return decrypted;
}
uint64_t   mod_inverse(uint64_t   a, uint64_t   m) {
    uint64_t   m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        uint64_t   q = a / m;
        uint64_t   t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    return x < 0 ? x + m0 : x;
}
uint64_t   find_k(uint64_t   g, uint64_t   a, uint64_t   p) {
    uint64_t   current = 1;
    for (uint64_t   k = 0; k < p; ++k) {
        if (current == a) return k;
        current = (current * g) % p;
    }
    return -1;
}
string attack(const vector<pair<uint64_t  , uint64_t  >>& encrypted, uint64_t   p, uint64_t   g, uint64_t  y) {
    if (encrypted.empty()) return "";
    uint64_t  a = encrypted[0].first;
    for (const auto& pair : encrypted) 
        if (pair.first != a) {
            cout << "Атака невозможна: разные a.\n";
            return "";
        }
    uint64_t  k = find_k(g, a, p);
    if (k == -1) {
        cout << "k не найден.\n";
        return "";
    }
    uint64_t  s = fast_pow(y, k, p);
    uint64_t  s_inv = mod_inverse(s, p);
    string result;
    for (const auto& pair : encrypted) {
        uint64_t  m = (pair.second * s_inv) % p;
        result += static_cast<char>(m);
    }
    return result;
}