#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"
#include "minha_string.h"

Jogador* criarJoga(char* nome, char* idade, char* pont, char* profissao){
    Jogador *j = malloc(sizeof(Jogador));
    if (j == NULL) return NULL;
    
	j ->nome = malloc(100 * sizeof(char));
	j ->idade = malloc(5 * sizeof(char));
	j ->pont = malloc (20 * sizeof(char));
	j ->profissao = malloc(50 * sizeof(char));

	copia_string(nome, j-> nome);
	copia_string(idade, j-> idade);
	copia_string(pont, j-> pont);
	copia_string(profissao, j->profissao);

	return j;
}

void liberar_jogador(Jogador* j){
    if(j == NULL) return;
    
    free(j->nome);
    free(j->idade);
    free(j->pont);
    free(j->profissao);
    
    free(j);
}
