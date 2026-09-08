#ifndef PERGUNTA_H
#define PERGUNTA_H

typedef struct p{
    char *enunciado;
    char *alt_a;
    char *alt_b;
    char *alt_c;
    char *alt_d;
    char resposta;
}Pergunta;

Pergunta* criarPerg(char*, char*, char*, char*, char*, char);
void imprime(Pergunta*);
void liberar_pergunta(Pergunta*);
int valida_resposta(Pergunta*);

#endif