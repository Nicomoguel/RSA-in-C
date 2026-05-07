#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "./utils/headers.h"
#include "./utils/algorithms.h"
typedef long long ll;

void filecopy_enc(FILE *ifr, FILE *ofr, ll key, ll n, Nodo **lista);
void filecopy_dec(FILE *ofr, ll key, ll n, Nodo *lista);

int main(int argc, char *argv[]){
    
    srand(time(NULL));
    Nodo *lista = NULL;
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
            continuar();
            break;
        
        case 'b':
            limpiar_pantalla();
            header_b();
            printf("Ingresa tu llave pública: ");
            scanf("%lld", &e);
            while(getchar()!='\n');
            printf("Ingresa tu módulo: ");
            scanf("%lld", &n);
            while(getchar()!='\n');
            fr = fopen("01-original.txt", "r");
            fp = fopen("02-encriptado.txt", "w");
            filecopy_enc(fr, fp, e, n, &lista);  
            printf("Tu archivo ha quedado encriptado en 02-encriptado.txt\n");
            continuar();
            fclose(fr);
            fclose(fp);
            break;
        
        case 'c':
            limpiar_pantalla();
            header_c();
            printf("Ingresa tu llave privada: ");
            scanf("%lld", &d);
            while(getchar()!='\n');
            printf("Ingresa tu módulo: ");
            scanf("%lld", &n);
            while(getchar()!='\n');
            fp = fopen("03-desencriptado.txt", "w");
            filecopy_dec(fp, d, n, lista);
            fclose(fp);
            printf("Tu archivo ha quedado desencriptado en 03-desencriptado.txt\n");
            continuar();
            break;
        
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

void filecopy_enc(FILE *ifr, FILE *ofr, ll key, ll n, Nodo **lista){
    ll c;
    while((c = getc(ifr)) != EOF){
        c = encriptar(c, key, n);
        insertar(lista, c);
        fprintf(ofr, "%lld\n", c);
    } 
}

void filecopy_dec(FILE *ofr, ll key, ll n, Nodo *lista){
    Nodo *actual = lista;
    if(actual == NULL){
        FILE *fp = fopen("02-encriptado.txt", "r");
        ll c;
        while(fscanf(fp ,"%lld", &c) != EOF){
            c = desencriptar(c, key, n);
            fprintf(ofr, "%c", (char)c);
        }
    }else{
        while(actual != NULL){
                ll c = desencriptar(actual->valor, key, n);
                fprintf(ofr, "%c", (char)c);
                actual = actual->sig;
        }
    }
    
}