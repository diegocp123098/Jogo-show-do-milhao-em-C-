#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista_enc.h"
#include "arq.h"
#include "pergunta.h"
#include "jogador.h"
#include "minha_string.h"

#define TOTAL_RODADAS 5
#define VIDAS_INICIAIS 2               
#define MAX_ERROS (VIDAS_INICIAIS + 1) 
#define RODADA_CHECKPOINT 2            

//Trabalho de Estrutura de dados: Diego Pinheiro e João Barão
//Show do milhão

void ler_linha(char *destino, int tamanho_max)
{
    char temp[256];

    if (fgets(temp, sizeof(temp), stdin) == NULL) {
        destino[0] = '\0';
        return;
    }

    int len = 0;
    while (temp[len] != '\0' && temp[len] != '\n') {
        len++;
    }
    temp[len] = '\0';

    int i = 0;
    while (i < tamanho_max - 1 && temp[i] != '\0') {
        destino[i] = temp[i];
        i++;
    }
    destino[i] = '\0';
}

int main()
{
    srand(time(NULL)); 

    const char *valores[TOTAL_RODADAS] = {
        "R$ 1.000,00",
        "R$ 2.000,00",
        "R$ 5.000,00",
        "R$ 10.000,00",
        "R$ 50.000,00"
    };

    printf("=== SHOW DO MILHÃO ===\n\n");

    char nome[100];
    char idade[5];
    char profissao[50];

    printf("Digite seu nome: ");
    ler_linha(nome, sizeof(nome));

    printf("Digite sua idade: ");
    ler_linha(idade, sizeof(idade));

    printf("Digite sua profissão: ");
    ler_linha(profissao, sizeof(profissao));

    Jogador *jogador = criarJoga(nome, idade, "R$ 0,00", profissao);
    if (jogador == NULL) {
        printf("Não foi possível cadastrar o jogador.\n");
        return 1;
    }

    printf("\nBoa sorte, %s! Vamos começar!\n\n", jogador->nome);

    printf("=== SAO %d QUESTOES, VALORES DE %s ATE %s ===\n",
           TOTAL_RODADAS, valores[0], valores[TOTAL_RODADAS - 1]);
    printf("=== VOCE PODE ERRAR ATE %d VEZES. NO %dº ERRO VOCE E DESQUALIFICADO! ===\n\n",
           VIDAS_INICIAIS, MAX_ERROS);

    int rodada = 0;
    int erros = 0;
    int premio_garantido = -1; 
    int desqualificado = 0;

    while (rodada < TOTAL_RODADAS && erros < MAX_ERROS) {

        Lista *minha_lista = carregar_questoes();

        if (minha_lista == NULL || eh_vazia(minha_lista)) {
            printf("Nenhuma questão foi carregada.\n");
            liberar_jogador(jogador);
            return 1;
        }

        int total_questoes = tamanho_lista(minha_lista);
        int indice_sorteado = rand() % total_questoes;

        Elemento *aux = obter_primeiro(minha_lista);
        int i = 0;
        while (i < indice_sorteado && aux != NULL) {
            aux = obter_proximo(aux);
            i++;
        }

        int acertou = 0;

        if (aux != NULL) {
            Pergunta *pergunta_sorteada = (Pergunta*) obter_dado(aux);
            if (pergunta_sorteada != NULL) {
                printf("=== QUESTAO %d de %d | Valendo %s | Vidas restantes: %d ===\n",
                       rodada + 1, TOTAL_RODADAS, valores[rodada], VIDAS_INICIAIS - erros);
                imprime(pergunta_sorteada);
                acertou = valida_resposta(pergunta_sorteada);
            }
        }

        aux = obter_primeiro(minha_lista);
        while (aux != NULL) {
            Pergunta *p = (Pergunta*) obter_dado(aux);
            if (p != NULL) {
                liberar_pergunta(p);
            }
            aux = obter_proximo(aux);
        }

        liberar(minha_lista);

        if (acertou) {
            printf("Você garantiu %s!\n\n", valores[rodada]);

            if (rodada == RODADA_CHECKPOINT) {
                premio_garantido = rodada;
                printf(">>> PATAMAR SEGURO ATINGIDO! Mesmo se for desqualificado depois, você leva no mínimo %s. <<<\n\n",
                       valores[premio_garantido]);
            }

            rodada++;
        } else {
            erros++;

            if (erros >= MAX_ERROS) {
                desqualificado = 1;
                printf("=== Essa foi a %dª resposta errada. VOCÊ FOI DESQUALIFICADO! ===\n", erros);
            } else {
                printf("=== Você errou! Restam %d vida(s). Uma nova pergunta do mesmo valor será sorteada. ===\n\n",
                       VIDAS_INICIAIS - erros);
            }
        }
    }

    char premio_final[20];
    if (desqualificado) {
        if (premio_garantido >= 0) {
            copia_string((char*) valores[premio_garantido], premio_final);
        } else {
            copia_string("R$ 0,00", premio_final);
        }
    } else if (rodada >= TOTAL_RODADAS) {
        copia_string((char*) valores[TOTAL_RODADAS - 1], premio_final);
    } else {
        copia_string("R$ 0,00", premio_final);
    }
    copia_string(premio_final, jogador->pont);

    printf("\n================ FIM DE JOGO ================\n");
    if (desqualificado) {
        if (premio_garantido >= 0) {
            printf("%s foi desqualificado(a), mas leva o prêmio garantido: %s\n", jogador->nome, jogador->pont);
        } else {
            printf("%s foi desqualificado(a) antes de garantir qualquer prêmio. Leva R$ 0,00.\n", jogador->nome);
        }
    } else if (rodada >= TOTAL_RODADAS) {
        printf("PARABÉNS, %s! Você acertou todas as %d questões e levou o prêmio máximo: %s\n",
               jogador->nome, TOTAL_RODADAS, jogador->pont);
    }

    printf("\n--- Resumo do jogador ---\n");
    printf("Nome: %s\n", jogador->nome);
    printf("Idade: %s\n", jogador->idade);
    printf("Profissão: %s\n", jogador->profissao);
    printf("Prêmio final: %s\n", jogador->pont);

    liberar_jogador(jogador);

    return 0;
}
