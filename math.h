#include <tuple> 
#include <vector>
#include <cstdint>
using namespace std;
tuple<uint64_t, uint64_t , uint64_t > Euclid(uint64_t c, uint64_t m);// 
bool is_prime(int n);
uint64_t gcd(uint64_t a, uint64_t b);
uint64_t fast_pow(uint64_t a, uint64_t x, uint64_t p );
uint64_t binary_exponentiation(uint64_t a, uint64_t x,uint64_t p);
uint64_t fermat_method(uint64_t a, uint64_t x, uint64_t p);
vector<uint64_t > continuedFraction(uint64_t   p, uint64_t  q);
uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t mod);

