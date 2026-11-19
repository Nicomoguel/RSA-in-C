# RSA Encryption Engine in C

A menu-driven command-line tool that generates RSA key pairs and encrypts and decrypts text files. All of the number theory is implemented by hand in C, with no big-number library.

It began as a team course project at Universidad Autónoma de Yucatán (UADY).

## What it does

1. **Key generation:** picks two random primes `p` and `q`, computes `n = p·q` and Euler's totient, chooses a public exponent `e` coprime with the totient, and derives the private exponent `d` with the extended Euclidean algorithm.
2. **Encryption:** reads `01-original.txt` and writes each character as `C = M^e mod n` to `02-encriptado.txt`.
3. **Decryption:** reads the ciphertext back and writes `M = C^d mod n` to `03-desencriptado.txt`.

## Implementation notes

All arithmetic uses 64-bit signed integers (`long long`), in `utils/algorithms.c`:

- **`mul_mod`: overflow-safe modular multiplication.** Computing `a·b mod n` directly would overflow 64 bits once `n` passes about 2^31. `mul_mod` multiplies by repeated doubling and subtracts `mod` before each addition could overflow, so intermediate values never exceed `n`.
- **`power_mod`: square-and-multiply exponentiation** in O(log e) multiplications, built on `mul_mod`.
- **`miller_rabin`: Miller–Rabin primality test** with the first 12 primes (2 to 37) as witnesses. That set is enough for a correct answer on every 64-bit input.
- **`mcd_extendido`: recursive extended Euclidean algorithm**, used to get the modular inverse `d` of `e`.
- Ciphertext blocks are kept in a singly linked list that is freed explicitly after use.

**Limits.** Primes are below 2^31, so `n` fits in 64 bits. That makes this a learning implementation of the algorithms, not secure cryptography: real RSA keys are 2048+ bits and need padding such as OAEP. The `Research-Docs-Sprint1/` notes (in Spanish) include a look at GNU GMP for big numbers, but the final code doesn't use it.

## Build and run

Requires `gcc` and `make`.

```bash
make        # builds the 'rsa' executable
make run    # builds and runs it
make clean  # removes object files and the executable
```

## Project structure

```
main.c                  menu and the encrypt/decrypt file flow
utils/algorithms.c/.h   mul_mod, power_mod, Miller–Rabin, extended Euclid, key generation
utils/headers.c/.h      console menus and screens
Research-Docs-Sprint1/  research notes written during the first sprint (Spanish)
```
