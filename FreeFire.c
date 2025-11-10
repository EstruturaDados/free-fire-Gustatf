#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10


// Estrutura que representa um item do inventário

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;


// Declaração das funções

void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);
int buscarIndice(Item mochila[], int qtd, char nome[]);


// Função principal

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    do {
        printf("\n========== INVENTÁRIO DO JOGADOR ==========\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();                     // limpa buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nSaindo do inventário...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}


// Função: inserirItem()  "Permite ao jogador cadastrar um novo item"

void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n=== Inserindo novo item ===\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';            // remove \n

    printf("Tipo do item (arma, munição, cura...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(mochila, *qtd);
}


// Função: removerItem()    "Remove um item do inventário pelo nome"

void removerItem(Item mochila[], int *qtd) {
    char nomeRemover[30];
    printf("\n=== Remover item ===\n");
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int indice = buscarIndice(mochila, *qtd, nomeRemover);
    if (indice == -1) {
        printf("\nItem não encontrado!\n");
        return;
    }

    // Desloca os elementos após o item removido

    for (int i = indice; i < (*qtd) - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*qtd)--;

    printf("\nItem removido com sucesso!\n");
    listarItens(mochila, *qtd);
}


// Função: listarItens()       "Exibe todos os itens cadastrados"

void listarItens(Item mochila[], int qtd) {
    printf("\n=== Itens na mochila ===\n");

    if (qtd == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}


// Função: buscarItem()       "Localiza um item pelo nome (busca sequencial)" 

void buscarItem(Item mochila[], int qtd) {
    char nomeBuscar[30];
    printf("\n=== Buscar item ===\n");
    printf("Digite o nome do item: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    int indice = buscarIndice(mochila, qtd, nomeBuscar);

    if (indice == -1) {
        printf("\nItem não encontrado!\n");
    } else {
        printf("\nItem encontrado:\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[indice].nome, mochila[indice].tipo, mochila[indice].quantidade);
    }
}


// Função auxiliar: buscarIndice()      "Retorna o índice de um item pelo nome, ou -1 se não existir"

int buscarIndice(Item mochila[], int qtd, char nome[]) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}
