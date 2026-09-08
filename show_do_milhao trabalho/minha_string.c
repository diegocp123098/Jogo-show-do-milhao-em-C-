#include "minha_string.h"

int contar_vogais(char s[]) {
    int i = 0, contador = 0;
    while(s[i] != '\0') {
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
            contador++;
        }
        i++;
    }
    return contador;
}

int tamanho(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;
}

void copia_string(char s1[], char s2[]){
    int i = 0;
    while(s1[i] != '\0') {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
}

void inverter_string(char s1[], char s2[]) {
    int tam = tamanho(s1) - 1;
    int i = 0;
    while(tam >= 0) {
        s2[i] = s1[tam];
        tam --;
        i++;
    }
    s2[i] = '\0';
}

void concatenar_string(char s1[], char s2[], char s3[]) {
    int tam1 = tamanho(s1) - 1;
    int tam2 = tamanho(s2) - 1;
    int tam3 = tam1 + tam2;
    int i = 0, j = 0;
    while(s1[i] != '\0') {
        s3[i] = s1[i];
        i++;
    }
    while(s2[j] != '\0') {
        s3[i] = s2[j];
        i++;
        j++;
    }
    s3[tam3+1] = '\0';
}

int strings_sao_iguais(char s1[], char s2[]) {
    if(tamanho(s1) != tamanho(s2)) {
        return 0;
    }
    int i = 0;
    while(s1[i] != '\0') {
        if(s1[i] != s2[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}
