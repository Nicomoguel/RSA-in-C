# RSA — Introducción y Contexto

## ¿Qué es RSA?

RSA (Rivest–Shamir–Adleman) es un sistema de cifrado **asimétrico** publicado en 1977 por Ron Rivest, Adi Shamir y Leonard Adleman en el MIT. Es uno de los algoritmos criptográficos más utilizados en el mundo y constituye la base de protocolos como HTTPS, SSH y TLS.

A diferencia del cifrado simétrico (donde emisor y receptor comparten la misma llave), RSA utiliza **dos llaves distintas pero matemáticamente relacionadas**:

| Llave | Nombre | Uso |
|-------|--------|-----|
| `(e, n)` | Llave pública | Cifrar mensajes — puede ser conocida por todos |
| `(d, n)` | Llave privada | Descifrar mensajes — solo la conoce el propietario |

## ¿Por qué es seguro?

La seguridad de RSA se basa en la dificultad computacional de un problema matemático conocido como **factorización de enteros grandes**: dado el número `n = p × q`, es prácticamente imposible encontrar `p` y `q` de forma eficiente cuando ambos son primos de cientos de dígitos.

Aunque multiplicar dos primos grandes es trivial, la operación inversa (factorizar el producto) requeriría miles de años con el hardware actual si los primos tienen más de 1024 bits.

## Flujo general del sistema

```
[Generación de llaves]
    p, q → n = p×q → φ(n) = (p-1)(q-1) → e, d

[Cifrado] (llave pública)
    Mensaje M → C = M^e mod n

[Descifrado] (llave privada)
    Cifrado C → M = C^d mod n
```

## ¿Por qué lo implementamos en C?

C permite control directo sobre la memoria y la aritmética de bajo nivel, lo cual es esencial cuando se trabaja con números de 128 bits o más. Junto con la biblioteca GMP (GNU Multiple Precision Arithmetic Library), podemos realizar operaciones sobre números enormes que no caben en los tipos primitivos del lenguaje.

## Referencias

- Rivest, R. L., Shamir, A., & Adleman, L. (1978). *A method for obtaining digital signatures and public-key cryptosystems.* Communications of the ACM, 21(2), 120–126.
- Stallings, W. (2017). *Cryptography and Network Security: Principles and Practice* (7th ed.). Pearson.
