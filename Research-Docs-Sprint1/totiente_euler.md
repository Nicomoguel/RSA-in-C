# Totiente de Euler — φ(n)

## ¿Qué es el totiente de Euler?

El **totiente de Euler** (escrito `φ(n)`, leído "fi de n") de un entero positivo `n` es la cantidad de números enteros entre `1` y `n` que son **coprimos** con `n` (es decir, que su máximo común divisor con `n` es 1).

### Ejemplos simples

- `φ(8) = 4` → los coprimos de 8 menores que él son: 1, 3, 5, 7
- `φ(7) = 6` → como 7 es primo, todos los números del 1 al 6 son coprimos con él

## Propiedad clave para RSA

Cuando `n = p × q` con `p` y `q` primos distintos, el totiente se simplifica de forma notable:

```
φ(n) = φ(p) × φ(q) = (p - 1)(q - 1)
```

Esto es posible porque los únicos números entre 1 y `n` que **no** son coprimos con `n` son los múltiplos de `p` y los múltiplos de `q`.

## Implementación en el proyecto

```c
mpz_sub_ui(p1, p, 1);   // p1 = p - 1
mpz_sub_ui(q1, q, 1);   // q1 = q - 1
mpz_mul(tot, p1, q1);   // tot = (p-1)(q-1)
```

> **Nota sobre un bug conocido:** En la versión inicial de `euclides.c`, la línea `mpz_sub_ui(q1, p, 1)` tenía un error tipográfico (usaba `p` en lugar de `q`). Esto fue corregido en `main.c` usando `mpz_sub_ui(q1, q, 1)`.

## ¿Para qué lo usamos en RSA?

El totiente `φ(n)` nos permite calcular el exponente privado `d` como el **inverso modular** de `e` respecto a `φ(n)`. Esto funciona gracias al **Teorema de Euler**, que nos garantiza que:

```
e × d ≡ 1 (mod φ(n))
```

Lo que implica que:

```
(M^e)^d ≡ M (mod n)
```

Es decir, cifrar con `e` y luego descifrar con `d` nos devuelve el mensaje original `M`.

## ¿Por qué no se puede calcular φ(n) sin conocer p y q?

Calcular `φ(n)` directamente desde `n` requiere factorizarlo (encontrar `p` y `q`). Y factorizar `n` cuando sus factores son primos grandes es computacionalmente inviable — de ahí la seguridad de RSA.

El atacante conoce `n` (es público), pero sin `p` y `q` no puede calcular `φ(n)` y, por lo tanto, no puede obtener `d`.

## Referencias

- Euler, L. (1763). *Theoremata arithmetica nova methodo demonstrata.*
- Hardy, G. H., & Wright, E. M. (2008). *An Introduction to the Theory of Numbers* (6th ed.). Oxford University Press.
