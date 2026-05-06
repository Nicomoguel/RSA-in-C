# PES-Project — Algoritmo de RSA en C

Implementación de un sistema de cifrado asimétrico RSA en C, estructurado en tres fases:

1. **Generación de llaves** — selección de primos `p` y `q`, cálculo del módulo `n` y obtención de la llave pública `e` y privada `d` mediante el Algoritmo de Euclides Extendido.
2. **Cifrado** *(Sprint 2)* — transformación de bloques de texto (ASCII) a valores numéricos procesados bajo la fórmula `C = M^e (mod n)`.
3. **Descifrado** *(Sprint 3)* — reversión del proceso mediante la llave privada usando `M = C^d (mod n)`.

## Requisitos

- `gcc`
- `libgmp-dev` (GNU Multiple Precision Arithmetic Library)

```bash
# Ubuntu / Debian
sudo apt install gcc libgmp-dev
```

## Compilación y ejecución

```bash
make        # Compila el proyecto → genera el ejecutable 'rsa'
make run    # Compila y ejecuta
make clean  # Elimina archivos objeto y el ejecutable
```

## Estructura del proyecto

```
pes-project/
├── main.c                          # Punto de entrada: orquesta las 3 fases RSA
├── euclides.c                      # Algoritmo de Euclides Extendido (GCD)
├── euclides.h                      # Declaraciones de euclides.c
├── Makefile                        # Reglas de compilación
├── .gitignore                      # Ignora ejecutables y archivos objeto
└── Research-Docs-Sprint1/
    └── algoritmo_euclides.md       # Documentación del algoritmo GCD
```

## Pendientes
```
 -organizar la estructura con los header files.
 -hacer las diapositivas para la presentacion final.
 ```