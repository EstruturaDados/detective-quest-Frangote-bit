#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Estrutura da sala da mansão
//
typedef struct Sala {
    char nome[50];
    char pista[100];

    struct Sala *esquerda;
    struct Sala *direita;

} Sala;

//
// Estrutura da árvore BST de pistas
//
typedef struct PistaNode {
    char pista[100];

    struct PistaNode *esquerda;
    struct PistaNode *direita;

} PistaNode;

//
// Função: criarSala
// Cria dinamicamente uma sala da mansão
//
Sala* criarSala(char nome[], char pista[]) {

    Sala *novaSala = (Sala*) malloc(sizeof(Sala));

    if (novaSala == NULL) {
        printf("Erro de memoria!\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);

    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

//
// Função: criarPistaNode
// Cria um nó da BST de pistas
//
PistaNode* criarPistaNode(char pista[]) {

    PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));

    if (novo == NULL) {
        printf("Erro de memoria!\n");
        exit(1);
    }

    strcpy(novo->pista, pista);

    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

//
// Função: inserirPista
// Insere pistas em ordem alfabética na BST
//
PistaNode* inserirPista(PistaNode *raiz, char pista[]) {

    if (raiz == NULL) {
        return criarPistaNode(pista);
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    }
    else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

//
// Função: exibirPistas
// Mostra as pistas em ordem alfabética
//
void exibirPistas(PistaNode *raiz) {

    if (raiz != NULL) {

        exibirPistas(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        exibirPistas(raiz->direita);
    }
}

//
// Função: explorarSalasComPistas
// Controla a exploração da mansão
//
void explorarSalasComPistas(Sala *atual, PistaNode **arvorePistas) {

    char escolha;

    while (atual != NULL) {

        printf("\n=================================\n");
        printf("Voce esta em: %s\n", atual->nome);

        //
        // Verifica se existe pista
        //
        if (strlen(atual->pista) > 0) {

            printf("Pista encontrada: %s\n", atual->pista);

            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        //
        // Exibe opcoes
        //
        printf("\nEscolha um caminho:\n");

        if (atual->esquerda != NULL) {
            printf("e - Esquerda (%s)\n", atual->esquerda->nome);
        }

        if (atual->direita != NULL) {
            printf("d - Direita (%s)\n", atual->direita->nome);
        }

        printf("s - Sair\n");

        printf("Opcao: ");
        scanf(" %c", &escolha);

        //
        // Navegacao
        //
        if (escolha == 'e') {

            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            }
            else {
                printf("Nao existe sala a esquerda!\n");
            }

        }
        else if (escolha == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            }
            else {
                printf("Nao existe sala a direita!\n");
            }

        }
        else if (escolha == 's') {

            printf("\nExploracao encerrada.\n");
            break;

        }
        else {

            printf("Opcao invalida!\n");

        }
    }
}

//
// Libera memoria da árvore de salas
//
void liberarSalas(Sala *raiz) {

    if (raiz != NULL) {

        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);

        free(raiz);
    }
}

//
// Libera memoria da BST de pistas
//
void liberarPistas(PistaNode *raiz) {

    if (raiz != NULL) {

        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);

        free(raiz);
    }
}

//
// Função principal
//
int main() {

    //
    // Criacao das salas
    //
    Sala *hall = criarSala("Hall de Entrada", "");

    Sala *biblioteca = criarSala(
        "Biblioteca",
        "Livro rasgado encontrado"
    );

    Sala *cozinha = criarSala(
        "Cozinha",
        "Faca com manchas"
    );

    Sala *jardim = criarSala(
        "Jardim",
        "Pegadas na lama"
    );

    Sala *laboratorio = criarSala(
        "Laboratorio",
        "Frasco quebrado"
    );

    Sala *porao = criarSala(
        "Porao",
        "Corda escondida"
    );

    Sala *salaSecreta = criarSala(
        "Sala Secreta",
        "Carta suspeita"
    );

    //
    // Montagem da árvore binária
    //
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = laboratorio;
    biblioteca->direita = jardim;

    cozinha->esquerda = salaSecreta;
    cozinha->direita = porao;

    //
    // BST de pistas
    //
    PistaNode *arvorePistas = NULL;

    //
    // Inicio do jogo
    //
    printf("=================================\n");
    printf("      DETECTIVE QUEST\n");
    printf("=================================\n");

    explorarSalasComPistas(hall, &arvorePistas);

    //
    // Exibe pistas coletadas
    //
    printf("\n=================================\n");
    printf("PISTAS COLETADAS (ORDEM ALFABETICA)\n");
    printf("=================================\n");

    exibirPistas(arvorePistas);

    //
    // Libera memoria
    //
    liberarSalas(hall);
    liberarPistas(arvorePistas);

    return 0;
}