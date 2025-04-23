#include <stdio.h>
#include <windows.h>

#define LIN 100
#define COL 100

void gerarGrid(int porcentagemObstaculos);
void salvarGridNoTxt(char * grid[]);

int main() {
    int porcentagem;
    puts("Boas vindas ao sistema de navegacao para drones autonomos.");
    printf("Para gerar o mapa, informe a porcentagem de obstaculos no caminho:\n");
    do {
        printf("\t >");
        scanf("%d", &porcentagem);
    } while (porcentagem < 0 || porcentagem > 100);
    puts("Gerando o mapa...");
    Sleep(3000);
    gerarGrid(porcentagem);
}

void gerarGrid(int porcentagemObstaculos) {
    char grid[LIN][COL] = {{' '}};
    int qntdObstaculos = (LIN*COL) * (porcentagemObstaculos / 100);
    printf("%d", qntdObstaculos);
}

void salvarGridNoTxt(char * grid[]);