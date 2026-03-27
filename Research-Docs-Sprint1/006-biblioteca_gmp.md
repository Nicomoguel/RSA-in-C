# Biblioteca GMP — GNU Multiple Precision Arithmetic Library

## ¿Por qué necesitamos GMP?

Los tipos primitivos de C (`int`, `long`, `unsigned long long`) tienen un tamaño fijo: el mayor, `unsigned long long`, puede representar números de hasta **64 bits** (~1.8 × 10¹⁹).

RSA requiere trabajar con primos de **128 bits o más**, y su producto `n` tiene el doble de bits. Estos números simplemente no caben en los tipos estándar de C. GMP es la solución: permite operar sobre enteros de **precisión arbitraria**, limitados únicamente por la memoria del sistema.

## ¿Qué es GMP?

GMP (GNU Multiple Precision Arithmetic Library) es una biblioteca de C/C++ de código abierto, mantenida por el proyecto GNU. Está optimizada con rutinas en ensamblador para distintas arquitecturas y es considerada la implementación de referencia para aritmética de múltiple precisión.

- Sitio oficial: https://gmplib.org
- Licencia: LGPL v3

## Tipos de datos principales

En nuestro proyecto usamos exclusivamente el tipo `mpz_t`, diseñado para **enteros** de precisión arbitraria:

```c
mpz_t p;       // declaración
mpz_init(p);   // inicialización (reserva memoria)
// ... operaciones ...
mpz_clear(p);  // liberación de memoria (obligatorio)
```

> A diferencia de los tipos primitivos, GMP maneja su propia memoria dinámica. Olvidar `mpz_clear()` produce fugas de memoria.

## Funciones utilizadas en el proyecto

| Función | Uso en el proyecto |
|---|---|
| `mpz_init(x)` | Inicializa una variable `mpz_t` |
| `mpz_clear(x)` | Libera la memoria de una variable |
| `mpz_set(dest, src)` | Copia el valor de `src` en `dest` |
| `mpz_set_ui(x, n)` | Asigna un `unsigned long` a `mpz_t` |
| `mpz_mul(r, a, b)` | `r = a × b` |
| `mpz_sub_ui(r, a, n)` | `r = a - n` (n entero normal) |
| `mpz_tdiv_r(r, a, b)` | `r = a mod b` (residuo de división truncada) |
| `mpz_cmp_ui(a, n)` | Compara `a` con un entero normal; retorna 0 si son iguales |
| `mpz_urandomb(r, state, bits)` | Genera entero aleatorio de `bits` bits |
| `mpz_urandomm(r, state, n)` | Genera entero aleatorio en `[0, n)` |
| `mpz_probab_prime_p(n, reps)` | Test de primalidad de Miller-Rabin con `reps` rondas |
| `mpz_invert(r, a, m)` | `r = a⁻¹ mod m` (inverso modular) |
| `gmp_printf(fmt, ...)` | `printf` extendido con soporte para `%Zd` (imprime `mpz_t`) |
| `gmp_randinit_default(state)` | Inicializa generador aleatorio (Mersenne Twister) |
| `gmp_randseed_ui(state, seed)` | Establece semilla del generador |
| `gmp_randclear(state)` | Libera el generador aleatorio |

## Instalación

```bash
# Ubuntu / Debian
sudo apt install libgmp-dev

# Fedora / RHEL
sudo dnf install gmp-devel

# macOS
brew install gmp
```

## Compilación con GMP

Es necesario enlazar la biblioteca al compilar:

```bash
gcc -Wall main.c euclides.c -o rsa -lgmp
```

En nuestro proyecto esto está automatizado en el `Makefile` con la variable `LIBS = -lgmp`.

## Referencias

- GMP Team. (2023). *GNU MP: The GNU Multiple Precision Arithmetic Library* (versión 6.3). https://gmplib.org/manual/
