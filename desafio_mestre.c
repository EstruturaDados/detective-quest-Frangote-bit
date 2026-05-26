#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

//
// Estrutura das salas
//
typedef struct Sala {

    char nome[50];
    char pista[100];

    struct Sala *esquerda;
    struct Sala *direita;

} Sala;

//
// Estrutura da BST de pistas
//
typedef struct PistaNode {

    char pista[100];

    struct PistaNode *esquerda;
    struct PistaNode *direita;

} PistaNode;

//
// Estrutura da tabela hash
//
typedef struct HashNode {

    char pista[100];
    char suspeito[50];

    struct HashNode *prox;

} HashNode;

//
// Tabela hash
//
HashNode *tabelaHash[TAM_HASH];

//
// Funcao hash simples
//
int funcaoHash(char pista[]) {

    int soma = 0;

    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }

    return soma % TAM_HASH;
}

//
// criarSala()
// Cria dinamicamente uma sala
//
Sala* criarSala(char nome[], char pista[]) {

    Sala *nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

//
// Cria nó da BST
//
PistaNode* criarPistaNode(char pista[]) {

    PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));

    strcpy(novo->pista, pista);

    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

//
// inserirPista()
// Insere pista na BST
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
// Exibe pistas em ordem
//
void exibirPistas(PistaNode *raiz) {

    if (raiz != NULL) {

        exibirPistas(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        exibirPistas(raiz->direita);
    }
}

//
// inserirNaHash()
// Relaciona pista -> suspeito
//
void inserirNaHash(char pista[], char suspeito[]) {

    int indice = funcaoHash(pista);

    HashNode *novo = (HashNode*) malloc(sizeof(HashNode));

    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabelaHash[indice];

    tabelaHash[indice] = novo;
}

//
// encontrarSuspeito()
// Busca suspeito pela pista
//
char* encontrarSuspeito(char pista[]) {

    int indice = funcaoHash(pista);

    HashNode *atual = tabelaHash[indice];

    while (atual != NULL) {

        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }

        atual = atual->prox;
    }

    return "Desconhecido";
}

//
// Conta pistas relacionadas ao suspeito
//
int contarPistasSuspeito(PistaNode *raiz, char suspeito[]) {

    if (raiz == NULL) {
        return 0;
    }

    int contador = 0;

    char *suspeitoEncontrado = encontrarSuspeito(raiz->pista);

    if (strcmp(suspeitoEncontrado, suspeito) == 0) {
        contador = 1;
    }

    return contador +
           contarPistasSuspeito(raiz->esquerda, suspeito) +
           contarPistasSuspeito(raiz->direita, suspeito);
}

//
// verificarSuspeitoFinal()
// Faz a verificacao final
//
void verificarSuspeitoFinal(PistaNode *arvorePistas) {

    char suspeito[50];

    printf("\nDigite o nome do suspeito acusado: ");
    scanf(" %[^\n]", suspeito);

    int quantidade = contarPistasSuspeito(arvorePistas, suspeito);

    printf("\nPistas encontradas contra %s: %d\n",
           suspeito,
           quantidade);

    if (quantidade >= 2) {

        printf("Acusacao consistente! O suspeito pode ser o culpado.\n");

    } else {

        printf("Poucas evidencias. Acusacao inconsistente.\n");

    }
}

//
// explorarSalas()
// Navega pela mansao
//
void explorarSalas(Sala *atual,
                   PistaNode **arvorePistas) {

    char escolha;

    while (atual != NULL) {

        printf("\n=================================\n");
        printf("Voce esta em: %s\n", atual->nome);

        //
        // Verifica pista
        //
        if (strlen(atual->pista) > 0) {

            printf("Pista encontrada: %s\n",
                   atual->pista);

            printf("Suspeito associado: %s\n",
                   encontrarSuspeito(atual->pista));

            *arvorePistas =
                inserirPista(*arvorePistas,
                             atual->pista);
        }

        //
        // Menu
        //
        printf("\nEscolha:\n");

        if (atual->esquerda != NULL) {
            printf("e - Esquerda (%s)\n",
                   atual->esquerda->nome);
        }

        if (atual->direita != NULL) {
            printf("d - Direita (%s)\n",
                   atual->direita->nome);
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

        }
        else if (escolha == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            }

        }
        else if (escolha == 's') {

            break;

        }
        else {

            printf("Opcao invalida!\n");

        }
    }
}

//
// main()
// Programa principal
//
int main() {

    //
    // Inicializa tabela hash
    //
    for (int i = 0; i < TAM_HASH; i++) {
        tabelaHash[i] = NULL;
    }

    //
    // Relacoes pista -> suspeito
    //
    inserirNaHash(
        "Faca com manchas",
        "Mordomo"
    );

    inserirNaHash(
        "Pegadas na lama",
        "Jardineiro"
    );

    inserirNaHash(
        "Carta suspeita",
        "Mordomo"
    );

    inserirNaHash(
        "Livro rasgado",
        "Professor"
    );

    inserirNaHash(
        "Frasco quebrado",
        "Cientista"
    );

    //
    // Cria salas
    //
    Sala *hall =
        criarSala("Hall de Entrada", "");

    Sala *biblioteca =
        criarSala("Biblioteca",
                  "Livro rasgado");

    Sala *cozinha =
        criarSala("Cozinha",
                  "Faca com manchas");

    Sala *jardim =
        criarSala("Jardim",
                  "Pegadas na lama");

    Sala *laboratorio =
        criarSala("Laboratorio",
                  "Frasco quebrado");

    Sala *salaSecreta =
        criarSala("Sala Secreta",
                  "Carta suspeita");

    //
    // Monta árvore
    //
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = laboratorio;
    biblioteca->direita = jardim;

    cozinha->esquerda = salaSecreta;

    //
    // BST de pistas
    //
    PistaNode *arvorePistas = NULL;

    //
    // Inicia jogo
    //
    printf("=================================\n");
    printf("      DETECTIVE QUEST\n");
    printf("=================================\n");

    explorarSalas(hall, &arvorePistas);

    //
    // Exibe pistas
    //
    printf("\n=================================\n");
    printf("PISTAS COLETADAS\n");
    printf("=================================\n");

    exibirPistas(arvorePistas);

    //
    // Julgamento final
    //
    verificarSuspeitoFinal(arvorePistas);

    return 0;
}