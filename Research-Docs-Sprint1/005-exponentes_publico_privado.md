# Exponentes Público (e) y Privado (d)

## El exponente público — e

El exponente público `e` forma parte de la llave pública `(e, n)` y se utiliza para **cifrar** mensajes. Su elección debe cumplir tres condiciones:

1. `1 < e < φ(n)`
2. `gcd(e, φ(n)) = 1` → `e` y el totiente deben ser coprimos
3. `e ≠ 0` y `e ≠ 1` (valores degenerados que rompen el cifrado)

### Generación en el proyecto

Se elige `e` de forma aleatoria y se verifica con el Algoritmo de Euclides hasta encontrar uno que cumpla todas las condiciones:

```c
bool test;
do {
    mpz_urandomm(e, gmpRandState, tot); // e aleatorio en [0, φ(n))
    test = get_gcd(tot, e);             // verifica gcd(φ(n), e) == 1
} while (mpz_cmp_ui(e, 0) == 0 || test == 0 || mpz_cmp_ui(e, 1) == 0);
```

### ¿Por qué debe ser coprimo con φ(n)?

Si `gcd(e, φ(n)) ≠ 1`, no existe el inverso modular de `e` respecto a `φ(n)`, lo que significa que **no podríamos calcular `d`** y el sistema sería incapaz de descifrar.

> En implementaciones reales de RSA (como OpenSSL), se suele usar `e = 65537` por ser un número primo de Fermat que equilibra seguridad y eficiencia. Nosotros usamos un valor aleatorio por propósito educativo.

---

## El exponente privado — d

El exponente privado `d` forma parte de la llave privada `(d, n)` y se utiliza para **descifrar** mensajes. Se define como el **inverso modular** de `e` módulo `φ(n)`:

```
d ≡ e⁻¹ (mod φ(n))
```

Lo que equivale a decir que:

```
e × d ≡ 1 (mod φ(n))
```

### Cálculo en el proyecto

GMP tiene una función dedicada para esto:

```c
mpz_invert(d, e, tot); // d = e^(-1) mod φ(n)
```

Internamente, `mpz_invert` aplica el **Algoritmo de Euclides Extendido** (una extensión del algoritmo que ya implementamos en `get_gcd`), que no solo calcula el MCD sino también los coeficientes de Bézout:

```
e × d + φ(n) × k = 1
```

Tomando esa ecuación módulo `φ(n)`, se obtiene `e × d ≡ 1 (mod φ(n))`, es decir, `d`.

---

## ¿Por qué cifrar con e y descifrar con d funciona?

Sea `M` el mensaje original. El cifrado produce:

```
C = M^e mod n
```

Y el descifrado:

```
M' = C^d mod n = (M^e)^d mod n = M^(e×d) mod n
```

Como `e × d ≡ 1 (mod φ(n))`, por el **Teorema de Euler** se cumple que `M^(e×d) ≡ M (mod n)`, por lo tanto `M' = M`. El mensaje se recupera intacto.

---

## Seguridad de d

El exponente privado `d` no debe revelarse nunca. Un atacante que conozca `n` y `e` (ambos públicos) necesitaría factorizar `n` para obtener `φ(n)` y de ahí calcular `d`. Como se explicó en el documento del totiente, factorizar `n` es computacionalmente inviable para primos grandes.

## Referencias

- Cormen, T. H. et al. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press. Cap. 31: Number-Theoretic Algorithms.
- Menezes, A., van Oorschot, P., & Vanstone, S. (1996). *Handbook of Applied Cryptography*. CRC Press. (disponible en: https://cacr.uwaterloo.ca/hac/)
