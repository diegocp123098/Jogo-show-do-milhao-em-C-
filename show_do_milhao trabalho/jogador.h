#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct j{
    char *nome;
    char *idade;
    char *pont;
    char *profissao;
}Jogador;

Jogador* criarJoga(char*, char*, char*, char*);
void liberar_jogador(Jogador*);

#endif