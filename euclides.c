#include <stdio.h>
#include <stdbool.h>
#include <gmp.h>
#include <time.h>
bool get_gcd(mpz_t tot, mpz_t e);
int main(){
    gmp_randstate_t gmpRandState; //objeto que genera los numeros random (solo se declaro)
    unsigned long seed; // semilla para los numeros random
    gmp_randinit_default(gmpRandState); // inicializar el generador de numeros random (Mersene Twister Algorithm, estaria cabron hacerlo manualmente)
    seed = time(NULL); //semilla de time.h
    gmp_randseed_ui(gmpRandState, seed);
    // Paso 1. Seleccionar primos muy grandes

    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t p1;
    mpz_t q1;
    mpz_t tot;
    mpz_t e;
    mpz_t d;
    mpz_t gcd;
    mpz_init(p);
    mpz_init(q); // inicializar las variables para que tengan un espacio en la memoria
    mpz_init(n);
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(tot);
    mpz_init(e);
    mpz_init(d);
    mpz_init(gcd);
    
    do{
        mpz_urandomb(p, gmpRandState, 128); // q y q randoms
    }while(!mpz_probab_prime_p(p, 25));
    do{
        mpz_urandomb(q, gmpRandState, 128);
    }while(!mpz_probab_prime_p(q, 25));
    
    // ya tengo 2 numeros primos MUY grandes

    // Paso 2. Calcular n = p x q
    mpz_mul(n, p, q); // producto de p y q


    // Paso 3. Calcular el totiente de euler
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, p, 1);
    mpz_mul(tot, p1, q1);

    // Paso 4. Calcular exponente publico e
    // ahora, el exponente publico debe estar entre 1 < e < tot y gcd(e, p(n)) = 1
    bool test;
    do{
        mpz_urandomm(e, gmpRandState, tot);
        test = get_gcd(tot, e);
    }while(mpz_cmp_ui(e, 0) == 0 || test == 0 || mpz_cmp_ui(e, 1) == 0);
    // 
    // entonces ya tenemos e (exponente publico)


    // Paso 5. Calcular exponente privado d
    mpz_invert(d, e, tot);

    gmp_printf("First prime random number of 128 bytes (q): %Zd\n\n", p);
    gmp_printf("Second prime random number of 128 bytes (p): %Zd\n\n", q);
    gmp_printf("The product of p and q is: %Zd\n\n", n);
    gmp_printf("Euler totient of n is (p - 1)(q - 1): %Zd\n\n", tot);
    gmp_printf("Public exponent (e): %Zd\n\n", e);
    gmp_printf("Private exponent (d): %Zd\n\n", d);




    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(tot);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(gcd);
    // limpio por que ocupan chingo de espacio
    return 0;

}


bool get_gcd(mpz_t tot, mpz_t e){
    mpz_t u;
    mpz_t v;
    mpz_t mod;
    mpz_init(u);
    mpz_init(v);
    mpz_init(mod);
    mpz_set(u, tot);
    mpz_set(v, e);
    while(mpz_cmp_ui(v, 0) != 0){
        mpz_tdiv_r(mod, u, v);
        mpz_set(u, v);
        mpz_set(v, mod);
    }
    bool result = mpz_cmp_ui(u, 1);
    mpz_clear(mod);
    mpz_clear(v);
    mpz_clear(u);
    if(!result) return true;
    else return false;
}





