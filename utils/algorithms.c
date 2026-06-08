#include "algorithms.h"
#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>



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

void insertar(Nodo **lista, ll valor){
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo -> valor = valor;
    nuevo -> sig = NULL;
    if(*lista == NULL){
        *lista = nuevo;
        return;
    }
    Nodo *actual = *lista;
    while(actual->sig != NULL){
        actual = actual->sig;
    }
    actual -> sig = nuevo;
}

void validar_opc(char opc){
    while(opc != 'a' && opc != 'b' && opc != 'c' && opc != 'd'){
        printf("Opcion no valida, intentalo de nuevo: ");
        scanf("%c", &opc);
        while(getchar() != '\n');
        opc = tolower(opc);
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

void liberar(Nodo *nodo){
    Nodo *temp;
    while(nodo != NULL){
        temp = nodo;
        nodo = nodo->sig;
        free(temp);
    }
}
