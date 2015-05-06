#include "Random.h"

mtrandom mtrand_help:: r;

extern void mtsrand(size_t s) { mtrand_help()(s); }
extern size_t mtirand() { return mtrand_help()(); }
extern double mtdrand() { return mtrand_help()(1.0); }
