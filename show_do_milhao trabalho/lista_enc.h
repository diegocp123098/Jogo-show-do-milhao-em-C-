#ifndef LISTA_ENC_H
#define LISTA_ENC_H

#include <stdbool.h>

typedef struct elemento Elemento;
typedef Elemento* Lista;

Lista *criar();
void liberar(Lista* l);
void inserir_fim(Lista *l, void *valor);
bool eh_vazia(Lista *l);
int tamanho_lista(Lista *l);
Elemento* obter_primeiro(Lista* l);
Elemento* obter_proximo(Elemento* e);
void* obter_dado(Elemento* e);

#endif