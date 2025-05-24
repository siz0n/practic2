#include <vector>
#include <iostream>
#include <cstdint>



using namespace std;
vector<pair<uint64_t , uint64_t >> encrypt(const string& message, uint64_t  p, uint64_t  k, uint64_t  g, uint64_t  y);
string decrypt(const vector<pair<uint64_t , uint64_t >>& encrypted, uint64_t  p, uint64_t  x);
uint64_t  mod_inverse(uint64_t  a, uint64_t  m);
string attack(const vector<pair<uint64_t , uint64_t >>& encrypted, uint64_t  p, uint64_t  g, uint64_t  y);
uint64_t  find_k(uint64_t  g, uint64_t  a, uint64_t  p);