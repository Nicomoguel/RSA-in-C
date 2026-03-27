#include "euclides.h"

// Algoritmo de Euclides Extendido
// Retorna true si gcd(tot, e) == 1 (son coprimos)
bool get_gcd(mpz_t tot, mpz_t e) {
    mpz_t u;
    mpz_t v;
    mpz_t mod;
    mpz_init(u);
    mpz_init(v);
    mpz_init(mod);
    mpz_set(u, tot);
    mpz_set(v, e);
    while (mpz_cmp_ui(v, 0) != 0) {
        mpz_tdiv_r(mod, u, v);
        mpz_set(u, v);
        mpz_set(v, mod);
    }
    bool result = mpz_cmp_ui(u, 1);
    mpz_clear(mod);
    mpz_clear(v);
    mpz_clear(u);
    if (!result) return true;
    else return false;
}
