#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "minha_string.h"
#include "pergunta.h"

Pergunta* criarPerg(char* enunciado, char* alt_a, char* alt_b, char* alt_c, char* alt_d, char resposta) {
	Pergunta *p = malloc(sizeof(Pergunta));
	p ->enunciado = malloc(200 * sizeof(char));
	p ->alt_a = malloc(40 * sizeof(char));
	p ->alt_b = malloc(40 * sizeof(char));
	p ->alt_c = malloc(40 * sizeof(char));
	p ->alt_d = malloc(40 * sizeof(char));

	copia_string(enunciado, p->enunciado);
	copia_string(alt_a, p->alt_a);
	copia_string(alt_b, p->alt_b);
	copia_string(alt_c, p->alt_c);
	copia_string(alt_d, p->alt_d);
	p->resposta = resposta;

	return p;
}

void imprime(Pergunta *p) {
	printf("%s\n", p->enunciado);
	printf("a) %s\n", p->alt_a);
	printf("b) %s\n", p->alt_b);
    printf("c) %s\n", p->alt_c);
    printf("d) %s\n", p->alt_d);
}

void liberar_pergunta(Pergunta *p){
    if (p == NULL) return;
    free(p->enunciado);
    free(p->alt_a);
    free(p->alt_b);
    free(p->alt_c);
    free(p->alt_d);
    free(p);
    
}

int valida_resposta(Pergunta *p){
    char opcao;
    int leitura_ok;

    do {
        printf("> ");
        leitura_ok = scanf(" %c", &opcao);

        // limpa o resto da linha pra não bagunçar a próxima leitura
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        if (leitura_ok != 1) {
            printf("\nEntrada encerrada.\n");
            return 0;
        }

        opcao = (char) tolower((unsigned char) opcao);

        if (opcao != 'a' && opcao != 'b' && opcao != 'c' && opcao != 'd') {
            printf("Opção inválida! Digite apenas a, b, c ou d.\n");
        }

    } while (opcao != 'a' && opcao != 'b' && opcao != 'c' && opcao != 'd');

    if(opcao == p->resposta){
        printf("Ceeeeeeeeerta resposta!!!\n\n");
        return 1;
    }else{
        printf("errrou :(\n A certa seria a %c\n\n", p->resposta);
        return 0;
    }
}