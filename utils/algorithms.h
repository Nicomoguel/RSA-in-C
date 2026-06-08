typedef long long ll;
#ifndef ALGORITHMS_H
#define ALGORITHMS_H
typedef struct Nodo{
    ll valor;
    struct Nodo *sig;
}Nodo;
void generar_llaves(ll *e, ll *d, ll *n);
ll mcd(ll u, ll v);
ll mcd_extendido(ll u, ll v, ll *x, ll *y);
ll encriptar(ll m, ll e, ll n);
ll desencriptar(ll c, ll d, ll n);
void validar_opc(char opc);
int miller_rabin(ll n);
ll power_mod(ll base, ll exp, ll mod);
ll mul_mod(ll a, ll b, ll mod);
void insertar(Nodo **lista, ll valor);
void liberar(Nodo *nodo);
#endif
