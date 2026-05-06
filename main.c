#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
typedef long long ll;
void filecopy_enc(FILE *ifr, FILE *ofr, ll key, ll n);
void filecopy_dec(FILE *ifr, FILE *ofr, ll key, ll n);
void validar_entrada(char str[41]);
void generar_llaves(ll *e, ll *d, ll *n);
ll mcd(ll u, ll v);
ll mcd_extendido(ll u, ll v, ll *x, ll *y);
ll encriptar(ll m, ll e, ll n);
ll desencriptar(ll c, ll d, ll n);
void limpiar_pantalla();
void header();
void header_a(ll e, ll d, ll n);
void validar_opc(char opc);
void header_b();
void header_c();
void continuar();
int miller_rabin(ll n);
ll power_mod(ll base, ll exp, ll mod);
ll mul_mod(ll a, ll b, ll mod);


int main(int argc, char *argv[]){
    srand(time(NULL));
    FILE *fr;
    FILE *fp;
    ll e, d, n;
    char opc;
    
    header();
    
    scanf("%c", &opc);
    while(getchar() != '\n');
    opc = tolower(opc);
    validar_opc(opc);
    
    
    while(1){
        switch (opc)
        {
        case 'a':
            limpiar_pantalla();
            generar_llaves(&e, &d, &n);
            header_a(e, d, n);
            return 0;
        
        case 'b':
            limpiar_pantalla();
            header_b();
            printf("Ingresa tu llave pública: ");
            scanf("%lld", &e);
            printf("Ingresa tu módulo: ");
            scanf("%lld", &n);
            fr = fopen("original.txt", "r");
            fp = fopen("encriptado.txt", "w");
            filecopy_enc(fr, fp, e, n);  
            printf("Tu archivo ha quedado encriptado en encriptado.txt\n");
            fclose(fr);
            return 0;
        
        case 'c':
            limpiar_pantalla();
            header_c();
            printf("Ingresa tu llave privada: ");
            scanf("%lld", &d);
            printf("Ingresa tu módulo: ");
            scanf("%lld", &n);
            fr = fopen("encriptado.txt", "r");
            fp = fopen("desencriptado.txt", "w");
            filecopy_dec(fr, fp, d, n);
            fclose(fr);
            printf("Tu archivo ha quedado desencriptado en desencriptado.txt\n");
            return 0;
        
        case 'd':
            return 0;
            break;
        }
        limpiar_pantalla();
        header();
        scanf("%c", &opc);
        while(getchar()!= '\n');
        opc = tolower(opc);
        validar_opc(opc);
    }
    
    return 0;
} 

void limpiar_pantalla(){
    #ifdef _WIN32
        system("cls");
    #else   
        system("clear");
    #endif
}





ll mul_mod(ll a, ll b, ll mod) {
    ll res = 0;
    a %= mod; 

    while (b > 0) {
        if (b & 1) {
            if (res >= mod - a) {
                res -= (mod - a);
            } else {
                res += a;
            }
        }
        if (b > 1) {
            if (a >= mod - a) {
                a -= (mod - a);
            } else {
                a += a;
            }
        }
        
        b >>= 1; 
    } return res;
}

ll power_mod(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod; 

    while (exp > 0) {
        if (exp & 1) {
            res = mul_mod(res, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    } return res;
}

int miller_rabin(ll n) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if (!(n & 1)) return 0;
    ll d = n - 1;
    int s = 0;
    while (!(d & 1)) {
        d >>= 1; 
        s++;
    }
    ll testigos[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (int i = 0; i < 12; i++) {
        ll a = testigos[i];
        if (n <= a) {break;}
        ll x = power_mod(a, d, n);
        if (x == 1 || x == n - 1) {continue;}
        int compuesto = 1;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                compuesto = 0; 
                break;
            }
        }
        if (compuesto) {return 0;}
    } return 1; 
}

ll numero(){ 
    ll num = rand();
    while(num > 2147483647 || !miller_rabin(num)){
        num = rand();
    }
    return num;
}

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

void validar_opc(char opc){
    while(opc != 'a' && opc != 'b' && opc != 'c' && opc != 'd'){
        printf("Opcion no valida, intentalo de nuevo: ");
        scanf("%c", &opc);
        while(getchar() != '\n');
        opc = tolower(opc);
    }
}

void filecopy_enc(FILE *ifr, FILE *ofr, ll key, ll n){
    ll c;
    while((c = getc(ifr)) != EOF){
        c = encriptar(c, key, n);
        fprintf(ofr, "%lld\n", c);
    } 
}

void filecopy_dec(FILE *ifr, FILE *ofr, ll key, ll n){
    ll c;
    while(fscanf(ifr ,"%lld", &c) != EOF){
        c = desencriptar(c, key, n);
        fprintf(ofr, "%c", (int)c);
    }
}

void generar_llaves(ll *e, ll *d, ll *n){
    ll tot, x, y;
    ll p = numero();
    ll q = numero();
    while(p == q){
        q = numero();
    }
    *n = p * q;
    tot = (p - 1) * (q - 1);
    for(*e = 2; *e < tot; (*e)++){
        if(mcd_extendido(tot, *e, &x, &y) == 1) break;
    }
    *d = (y % tot + tot) % tot;
}

ll mcd(ll u, ll v){
    ll x = 1, y = 1;
    return mcd_extendido(u,v,&x,&y);
}

ll mcd_extendido(ll u, ll v, ll *x, ll *y){
    if(u == 0){
        *x = 0;
        *y = 1;
        return v;
    }
    ll x1, y1;
    ll gcd = mcd_extendido(v % u, u, &x1, &y1);
    *x = y1 - (v / u) * x1;
    *y = x1;
    return gcd;

}

ll encriptar(ll m, ll e, ll n){
    return power_mod(m,e,n);
}

ll desencriptar(ll c, ll d, ll n){
    return power_mod(c, d, n);
}
