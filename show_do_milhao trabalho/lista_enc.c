#include <stdio.h>
#include <stdlib.h>
#include "lista_enc.h"

struct elemento{
	void *dado;
	struct elemento *prox;
};

Lista *criar(){
	Lista *l = (Lista*) malloc (sizeof(Lista));
	if(l==NULL) {
		return NULL;
	}	
	*l = NULL;
	return l;
}

void liberar(Lista* l){
	if(l == NULL){
	    if(l != NULL) free(l);
		return;
	}
	Elemento *aux = *l;
	while(aux != NULL){
		Elemento *prox = aux->prox;
        free(aux);
        aux = prox;
	}
	free(l);
}

void inserir_fim(Lista *l, void *valor){
    Elemento *e = (Elemento*) malloc (sizeof(Elemento));
    if(e == NULL){
        return;
    }
    e->dado = valor;
    e->prox = NULL;
    if((*l) == NULL){
        *l = e;
    } else {
        Elemento *aux = *l;
        while(aux -> prox != NULL){
            aux = aux -> prox;
        }
        aux -> prox = e;
    }
}

void imprimir(Lista *l){
	Elemento *aux = *l;
	while(aux != NULL){
		printf("%d ", aux -> dado);
		aux = aux -> prox;
	}
	printf("\n");
}

void remover_inicio(Lista *l){
	Elemento *aux = *l;
	(*l) = aux -> prox;
	free(aux);	
}

void remover_fim(Lista *l){
	Elemento *anterior, *atual = *l;
	while(atual->prox!=NULL){
		anterior = atual;
		atual = atual -> prox;
	}
	if(atual == (*l)){
		*l = atual -> prox;
	} else {
		anterior -> prox = atual -> prox;
	}
	free(atual);
}

bool eh_vazia(Lista *l){
	return l == NULL || (*l) == NULL;
}

int tamanho_lista(Lista *l){
	int tamanho = 0;
	Elemento *aux = *l;
	while(aux != NULL){
		tamanho++;
		aux = aux -> prox;
	}
	return tamanho;
}

Elemento* obter_primeiro(Lista* l) {
    if (l == NULL) return NULL;
    return *l;
}

Elemento* obter_proximo(Elemento* e) {
    if (e == NULL) return NULL;
    return e->prox;
}

void* obter_dado(Elemento* e) {
    if (e == NULL) return NULL;
    return e->dado;
}
