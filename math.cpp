#include <tuple> 
#include "math.h"
#include <cstdint>


using namespace std;
//--- 1. евклид
tuple<uint64_t, uint64_t , uint64_t > Euclid(uint64_t c, uint64_t m) { // 
    tuple<uint64_t, uint64_t , uint64_t > X = {c, 1, 0 } ;
    tuple<uint64_t, uint64_t , uint64_t > Y = {m, 0, 1};

    while (get<0>(Y) != 0) {
        int q = get<0>(X) / get<0>(Y); 
        
        tuple<uint64_t, uint64_t , uint64_t > T = make_tuple(
            get<0>(X) % get<0>(Y),              
            get<1>(X) - q * get<1>(Y),            
            get<2>(X) - q * get<2>(Y)             
        );
        X = Y; 
        Y = T; 
    }

    return X; 
}
// --- 2. Проверка на простоту--
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// --- 3. Алгоритм Евклида для НОД ---
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
/// --- 4. Возведение в степень
uint64_t fast_pow(uint64_t a,uint64_t x, uint64_t p ){
    uint64_t  result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * a) % p;
        }
        x = x / 2; 
        a = (a * a) % p;
    }
    return result;
}
// --- 5. Метод ферма
uint64_t fermat_method(uint64_t a, uint64_t x, uint64_t  p) {
    uint64_t new_x = x % (p - 1);
    return fast_pow(a, x, p);
}

// --- 6. Алгоритм через бинарное разложение 
uint64_t binary_exponentiation(uint64_t a, uint64_t x, uint64_t p) {
        if (p <= 1) return 0; // Некорректный модуль
        if (x == 0) return 1 % p; // a^0 mod p = 1 (при p > 1)
        
        uint64_t result = 1;
        a = a % p; // Гарантируем, что a < p
        
        while (x > 0) {
            // Если текущий бит x нечётный, умножаем результат на a
            if (x & 1) {
                result = (result * a) % p;
            }
            
            a = (a * a) % p;
            // Переходим к следующему биту
            x /= 2;
        }
        return result;
    }
    vector<uint64_t > continuedFraction(uint64_t p, uint64_t q) {
    vector<uint64_t > cf;
    while (q != 0) {
        uint64_t a = p / q;
        cf.push_back(a);
        uint64_t r = p % q;
        p = q;
        q = r;
    }
    return cf;
}
uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t result = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return result;
}