#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "algorithms.h"
void header() {
    limpiar_pantalla();
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║           BIENVENIDO A NUESTRO PROYECTO FINAL                ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                                                              ║\n");
    printf("║   Este programa implementa el algoritmo RSA para generar     ║\n");
    printf("║   llaves publicas y privadas.                                ║\n");
    printf("║                                                              ║\n");
    printf("║   Con la llave publica podemos ENCRIPTAR archivos,           ║\n");
    printf("║   pero estos solo se pueden DESENCRIPTAR con la llave        ║\n");
    printf("║   privada.                                                   ║\n");
    printf("║                                                              ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║               ¿QUE ACCION DESEAS REALIZAR?                   ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                                                              ║\n");
    printf("║   A. Generar llaves                                          ║\n");
    printf("║   B. Encriptar un archivo                                    ║\n");
    printf("║   C. Desencriptar un archivo                                 ║\n");
    printf("║   D. Salir del programa                                      ║\n");
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n   Opcion: ");
}
void header_a(ll e, ll d, ll n){
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                GENERADOR DE LLAVES USANDO RSA                ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                                                              ║\n");
    printf("║   El algoritmo RSA es un algoritmo de criptografia           ║\n");
    printf("║   asimetrico, que maneja una llave pública y una privada     ║\n");
    printf("║                                                              ║\n");
    printf("║   Para generar las llaves, se buscan p y q primos lo         ║\n");
    printf("║   suficientemente grandes, luego n=p*q y el totiente de      ║\n");
    printf("║   euler, se busca el exponente e tal que 1<e<Φ(n) y que      ║\n");
    printf("║   sea coprimo con Φ(n). Por último se busca el exponente     ║\n");
    printf("║   d tal que d sea el inverso modular multiplicativo de       ║\n");
    printf("║   e y Φ(n).                                                  ║\n");
    printf("║                                                              ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║               TUS LLAVES HAN SIDO GENERADAS                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("\tLlave pública: %lld", e);
    printf("\n");
    printf("\tMódulo: %lld", n);
    printf("\n");
    printf("\tLlave privada: %lld\n", d);
}

void header_b(){
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                     ¿CÓMO ENCRIPTAMOS?                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  La encriptación usa SÓLO la llave pública (e, n)            ║\n");
    printf("║                                                              ║\n");
    printf("║  Fórmula:  C ≡ M^e (mod n)                                   ║\n");
    printf("║                                                              ║\n");
    printf("║  Donde:                                                      ║\n");
    printf("║    C = texto cifrado (encrypted)                             ║\n");
    printf("║    M = mensaje original (message)                            ║\n");
    printf("║    e = exponente público                                     ║\n");
    printf("║    n = módulo público                                        ║\n");
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void header_c(){
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    ¿CÓMO DESENCRIPTAMOS?                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║  Sólo la llave PRIVADA (d, n) puede desencriptar             ║\n");
    printf("║                                                              ║\n");
    printf("║  Fórmula:  M ≡ C^d (mod n)                                   ║\n");
    printf("║                                                              ║\n");
    printf("║  Donde:                                                      ║\n");
    printf("║    M = mensaje original (recuperado)                         ║\n");
    printf("║    C = texto cifrado (encrypted)                             ║\n");
    printf("║    d = exponente PRIVADO                                     ║\n");
    printf("║    n = módulo público                                        ║\n");
    printf("║                                                              ║\n");
    printf("║    Tu archivo ha quedado guardado en desenciptado.txt        ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void continuar(){
    char c;
    printf("\nPresiona enter para continuar: ");
    scanf("%c", &c);
}

void limpiar_pantalla(){
    #ifdef _WIN32
        system("cls");
    #else   
        system("clear");
    #endif
}