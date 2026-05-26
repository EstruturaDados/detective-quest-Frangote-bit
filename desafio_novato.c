#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/*
    Função: criarSala
    Objetivo:
    Cria dinamicamente uma nova sala da mansão.
*/
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/*
    Função: explorarSalas
    Objetivo:
    Permite ao jogador navegar pela árvore binária,
    escolhendo esquerda (e), direita (d) ou sair (s).
*/
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        // Verifica se chegou em uma folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Nenhuma outra sala disponivel.\n");
            break;
        }

        printf("Escolha um caminho:\n");

        if (atual->esquerda != NULL) {
            printf("e - Ir para esquerda (%s)\n", atual->esquerda->nome);
        }

        if (atual->direita != NULL) {
            printf("d - Ir para direita (%s)\n", atual->direita->nome);
        }

        printf("s - Sair da exploracao\n");
        printf("Opcao: ");
        scanf(" %c", &escolha);

        if (escolha == 'e') {

            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao existe caminho para a esquerda!\n");
            }

        } else if (escolha == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao existe caminho para a direita!\n");
            }

        } else if (escolha == 's') {

            printf("Exploracao encerrada.\n");
            break;

        } else {

            printf("Opcao invalida!\n");

        }
    }
}

/*
    Função: liberarMemoria
    Objetivo:
    Libera toda a memória alocada para a árvore.
*/
void liberarMemoria(Sala *raiz) {
    if (raiz != NULL) {
        liberarMemoria(raiz->esquerda);
        liberarMemoria(raiz->direita);
        free(raiz);
    }
}

/*
    Função principal
    Objetivo:
    Monta o mapa da mansão e inicia a exploração.
*/
int main() {

    // Criacao das salas
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *cozinha = criarSala("Cozinha");
    Sala *laboratorio = criarSala("Laboratorio");
    Sala *jardim = criarSala("Jardim");
    Sala *salaSecreta = criarSala("Sala Secreta");
    Sala *porao = criarSala("Porao");

    // Montagem da arvore binaria
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = laboratorio;
    biblioteca->direita = jardim;

    cozinha->esquerda = salaSecreta;
    cozinha->direita = porao;

    // Inicio do jogo
    printf("=== Detective Quest ===\n");
    printf("Explore a mansao e encontre pistas!\n");

    explorarSalas(hall);

    // Liberacao da memoria
    liberarMemoria(hall);

    return 0;
}