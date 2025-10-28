#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Territorio* criarMapa(int qtd) {
    return (Territorio*) calloc(qtd, sizeof(Territorio));
}

void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do Exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n========================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("========================================\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        if (defensor->tropas <= 0) {
            printf("O territorio %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
            atacante->tropas /= 2;
        }
    } else {
        printf("DEFESA RESISTIU! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));
    int qtdTerritorios;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);
    limparBufferEntrada();

    Territorio* mapa = criarMapa(qtdTerritorios);
    cadastrarTerritorios(mapa, qtdTerritorios);

    int opcaoAtacante, opcaoDefensor;
    do {
        exibirMapa(mapa, qtdTerritorios);
        printf("--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", qtdTerritorios);
        scanf("%d", &opcaoAtacante);
        if (opcaoAtacante == 0) break;

        printf("Escolha o territorio defensor (1 a %d): ", qtdTerritorios);
        scanf("%d", &opcaoDefensor);

        if (opcaoAtacante < 1 || opcaoAtacante > qtdTerritorios ||
            opcaoDefensor < 1 || opcaoDefensor > qtdTerritorios ||
            opcaoAtacante == opcaoDefensor) {
            printf("Escolha invalida!\n");
        } else if (strcmp(mapa[opcaoAtacante - 1].cor, mapa[opcaoDefensor - 1].cor) == 0) {
            printf("Nao pode atacar territorio da mesma cor!\n");
        } else {
            atacar(&mapa[opcaoAtacante - 1], &mapa[opcaoDefensor - 1]);
        }

        limparBufferEntrada();
        printf("\nPressione Enter para continuar...");
        getchar();
    } while (1);

    liberarMemoria(mapa);
    return 0;
}