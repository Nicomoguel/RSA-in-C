# Números Primos y su Generación

## ¿Por qué necesitamos primos grandes?

RSA requiere dos números primos `p` y `q` como punto de partida. Su producto `n = p × q` forma el módulo del sistema. La seguridad depende de que `n` sea imposible de factorizar, lo que se logra eligiendo `p` y `q` suficientemente grandes (en nuestro caso, de **128 bits** cada uno, lo que da un `n` de ~256 bits).

## ¿Cómo los generamos?

No existe una fórmula para generar primos directamente. El proceso es:

1. Generar un número aleatorio grande
2. Comprobar si es primo
3. Si no lo es, repetir

```c
do {
    mpz_urandomb(p, gmpRandState, 128); // número aleatorio de 128 bits
} while (!mpz_probab_prime_p(p, 25));  // repetir si no es primo
```

## Test de primalidad de Miller-Rabin

Verificar si un número de 128 bits es primo de forma exacta (fuerza bruta) sería computacionalmente inviable. En su lugar usamos el **test probabilístico de Miller-Rabin**, implementado en GMP con la función `mpz_probab_prime_p(n, reps)`.

### ¿Cómo funciona?

El test se basa en una propiedad de los números primos derivada del Pequeño Teorema de Fermat. Para un primo `p` y cualquier base `a` con `1 < a < p-1`, se cumple que:

```
a^(p-1) ≡ 1 (mod p)
```

Miller-Rabin lo extiende: escribe `p-1 = 2^s × d` y verifica condiciones sobre `a^d mod p`. Si el número falla la prueba para alguna base `a`, definitivamente **no es primo**. Si la pasa, *probablemente* sí lo es.

### ¿Qué significa el parámetro 25?

El `25` en `mpz_probab_prime_p(p, 25)` indica el número de **rondas del test**. Cada ronda reduce la probabilidad de un falso positivo (un compuesto que parezca primo) a `1/4`. Con 25 rondas, la probabilidad de error es de aproximadamente:

```
(1/4)^25 ≈ 8.9 × 10^-16
```

Es decir, prácticamente cero para efectos prácticos.

### Valores de retorno

| Retorno | Significado |
|---------|-------------|
| `0`     | Definitivamente compuesto (no primo) |
| `1`     | Probablemente primo |
| `2`     | Definitivamente primo (para números pequeños verificados exactamente) |

## Generador de números aleatorios en GMP

Para que los primos generados no sean predecibles, usamos el generador de números pseudoaleatorios de GMP basado en el **algoritmo Mersenne Twister**:

```c
gmp_randstate_t gmpRandState;
gmp_randinit_default(gmpRandState);    // inicializa con Mersenne Twister
gmp_randseed_ui(gmpRandState, time(NULL)); // semilla basada en el tiempo actual
```

La semilla `time(NULL)` garantiza que cada ejecución produzca primos distintos.

## Referencias

- Miller, G. L. (1976). *Riemann's Hypothesis and Tests for Primality.* Journal of Computer and System Sciences.
- Rabin, M. O. (1980). *Probabilistic algorithm for testing primality.* Journal of Number Theory.
- GMP Manual: https://gmplib.org/manual/Number-Theoretic-Functions
