#include "arq.h"
#include "lista_enc.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pergunta.h"

char *pega_enunciado(char *linha, int *posicoes)
{
    char *enunciado = malloc (200 * sizeof(char));
    char *aux = linha; 
    int i = 0;
    while (i < *(posicoes))
    {
        *(enunciado+i) = *(aux+i);
        i++;
    }
    *(enunciado+i) = '\0';
    return enunciado;
}

char *pega_alternativa_a(char *linha, int *posicoes)
{
    char *alternativa_a = malloc (40 * sizeof(char));
    char *aux = linha;
    int i = *(posicoes+0)+1, j = 0;
    while (i < *(posicoes+1))
    {
        *(alternativa_a+j) = *(aux+i);
        i++;
        j++;
    }
    *(alternativa_a+j) = '\0';
    return alternativa_a;
}

char *pega_alternativa_b(char *linha, int *posicoes)
{
    char *alternativa_b = malloc (40 * sizeof(char));
    char *aux = linha; 
    int i = *(posicoes+1)+1, j = 0;
    while (i < *(posicoes+2))
    {
        *(alternativa_b+j) = *(aux+i);
        i++;
        j++;
    }
    *(alternativa_b+j) = '\0';
    return alternativa_b;
}

char *pega_alternativa_c(char *linha, int *posicoes)
{
    char *alternativa_c = malloc (40 * sizeof(char));
    char *aux = linha; 
    int i = *(posicoes+2)+1, j = 0;
    while (i < *(posicoes+3))
    {
        *(alternativa_c+j) = *(aux+i);
        i++;
        j++;
    }
    *(alternativa_c+j) = '\0';
    return alternativa_c;
}

char *pega_alternativa_d(char *linha, int *posicoes)
{
    char *alternativa_d = malloc (200 * sizeof(char));
    char *aux = linha;
    int i = *(posicoes+3)+1, j = 0;
    while (i < *(posicoes+4))
    {
        *(alternativa_d+j) = *(aux+i);
        i++;
        j++;
    }
    *(alternativa_d+j) = '\0';
    return alternativa_d;
}

char pega_resposta(char *linha, int *posicoes)
{
    char *aux = linha;
    int i = *(posicoes+4)+1;
    return *(aux+i);
}

Pergunta *separar_informacoes(char *linha, int *posicoes)
{
    char *enunciado = pega_enunciado(linha, posicoes);
    char *alternativa_a = pega_alternativa_a(linha, posicoes);
    char *alternativa_b = pega_alternativa_b(linha, posicoes);
    char *alternativa_c = pega_alternativa_c(linha, posicoes);
    char *alternativa_d = pega_alternativa_d(linha, posicoes);
    char resposta = pega_resposta(linha, posicoes);
    Pergunta *p = criarPerg(enunciado, alternativa_a, alternativa_b, alternativa_c, alternativa_d, resposta);
    
    free(enunciado);
    free(alternativa_a);
    free(alternativa_b);
    free(alternativa_c);
    free(alternativa_d);
    
    return p;
}

Pergunta *quebrar_linha(char *linha){
    int *posicoes = malloc(6 * sizeof(int));
    char *aux = linha;
    int i = 0, j = 0;
    while (*(aux + i) != '\0'){
        if (*(aux + i) == ','){
            *(posicoes + j) = i;
            j++;
        }
        i++;
    }
    Pergunta *p = separar_informacoes(linha, posicoes);
    free(posicoes);
    return p;
}

Lista *carregar_questoes() {
    Lista *l = criar();
    FILE *arq = fopen("questoes2.txt", "r");

    if (arq == NULL) {
        printf("arquivo de entrada nao encontrado\n");
        exit(1);
    }

    char *linha = malloc (200 * sizeof(char));

    while (fgets(linha, 200, arq) != NULL) {
        Pergunta *p = quebrar_linha(linha);
        inserir_fim(l, p);
    }
    free(linha);
    fclose(arq);
    return l;
}

