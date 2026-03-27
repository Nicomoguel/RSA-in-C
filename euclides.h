#ifndef EUCLIDES_H
#define EUCLIDES_H

#include <stdbool.h>
#include <gmp.h>

// Retorna true si gcd(tot, e) == 1 (coprimos), false en otro caso
bool get_gcd(mpz_t tot, mpz_t e);

#endif
