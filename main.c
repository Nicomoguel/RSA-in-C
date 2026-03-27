#include <stdio.h>
#include <time.h>
#include <gmp.h>
#include "euclides.h"

int main() {
    // === FASE 1: Generación de llaves ===
    gmp_randstate_t gmpRandState;
    unsigned long seed;

    gmp_randinit_default(gmpRandState); // Mersenne Twister
    seed = time(NULL);
    gmp_randseed_ui(gmpRandState, seed);

    mpz_t p, q, n, p1, q1, tot, e, d, gcd;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(tot);
    mpz_init(e);
    mpz_init(d);
    mpz_init(gcd);

    // Paso 1: seleccionar dos primos grandes de 128 bits
    do {
        mpz_urandomb(p, gmpRandState, 128);
    } while (!mpz_probab_prime_p(p, 25));
    do {
        mpz_urandomb(q, gmpRandState, 128);
    } while (!mpz_probab_prime_p(q, 25));

    // Paso 2: calcular n = p * q
    mpz_mul(n, p, q);

    // Paso 3: calcular el totiente de Euler φ(n) = (p-1)(q-1)
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(tot, p1, q1);

    // Paso 4: calcular exponente público e tal que gcd(e, φ(n)) = 1
    bool test;
    do {
        mpz_urandomm(e, gmpRandState, tot);
        test = get_gcd(tot, e);
    } while (mpz_cmp_ui(e, 0) == 0 || test == 0 || mpz_cmp_ui(e, 1) == 0);

    // Paso 5: calcular exponente privado d = e^(-1) mod φ(n)
    mpz_invert(d, e, tot);

    gmp_printf("Primo p (128 bits):       %Zd\n\n", p);
    gmp_printf("Primo q (128 bits):       %Zd\n\n", q);
    gmp_printf("Módulo n = p*q:           %Zd\n\n", n);
    gmp_printf("Totiente φ(n):            %Zd\n\n", tot);
    gmp_printf("Llave pública (e):        %Zd\n\n", e);
    gmp_printf("Llave privada (d):        %Zd\n\n", d);

    // === FASE 2: Cifrado (Sprint 2) ===
    // TODO: leer archivo .txt, convertir bloques a numérico, aplicar C = M^e mod n

    // === FASE 3: Descifrado (Sprint 3) ===
    // TODO: aplicar M = C^d mod n y reconstruir el archivo original

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(tot);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(gcd);
    gmp_randclear(gmpRandState);

    return 0;
}
